/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   coder_routine.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crodrigo <crodrigo@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/18 21:02:12 by crodrigo          #+#    #+#             */
/*   Updated: 2026/11/18 21:02:12 by crodrigo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

static void	complete_compile(t_coder *coder, unsigned long now)
{
	t_data	*data;

	data = coder->data;
	return_dongles(coder, now);
	if (!data->is_active)
		return ;
	monitor_deadlines(data, now);
	if (!data->is_active)
		return ;
	coder->completed_compile_count++;
	if (coder->completed_compile_count == data->required_compile_count)
		data->completed_coder_count++;
	if (data->completed_coder_count == data->coder_count)
		deactivate_simulation(data);
}

static void	run_phase(t_coder *coder, const char *action, unsigned int ms)
{
	unsigned long	now;
	t_data			*data;

	data = coder->data;
	if (!data->is_active)
		return ;
	now = current_microseconds();
	monitor_deadlines(data, now);
	if (!data->is_active)
		return ;
	emit_state(coder, action, now);
	sleep_until(data, now + ms * 1000UL);
}

static void	compile_cycle(t_coder *coder)
{
	unsigned long	now;
	t_data			*data;

	data = coder->data;
	if (!acquire_dongles(coder))
		return ;
	now = current_microseconds();
	monitor_deadlines(data, now);
	if (data->is_active)
	{
		coder->deadline = now + data->burnout_limit_ms * 1000UL;
		emit_state(coder, "has taken a dongle", now);
		emit_state(coder, "has taken a dongle", now);
		emit_state(coder, "is compiling", now);
		pthread_cond_broadcast(&data->state_changed);
		sleep_until(data, now + data->compile_duration_ms * 1000UL);
	}
	complete_compile(coder, current_microseconds());
	run_phase(coder, "is debugging", data->debug_duration_ms);
	run_phase(coder, "is refactoring", data->refactor_duration_ms);
}

void	*coder_thread(void *arg)
{
	t_coder	*coder;
	t_data	*data;

	coder = arg;
	data = coder->data;
	pthread_mutex_lock(&data->simulation_mutex);
	while (data->is_active
		&& coder->completed_compile_count < data->required_compile_count)
		compile_cycle(coder);
	pthread_mutex_unlock(&data->simulation_mutex);
	return (NULL);
}
