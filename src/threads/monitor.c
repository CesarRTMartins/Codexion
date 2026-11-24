/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crodrigo <crodrigo@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/18 21:02:19 by crodrigo          #+#    #+#             */
/*   Updated: 2026/11/18 21:02:19 by crodrigo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

unsigned long	monitor_deadlines(t_data *data, unsigned long now)
{
	unsigned int	i;
	t_coder			*earliest;
	t_coder			*coder;

	earliest = NULL;
	i = 0;
	while (i < data->coder_count)
	{
		coder = &data->coder_table[i++];
		if (coder->completed_compile_count < data->required_compile_count
			&& (!earliest || coder->deadline < earliest->deadline))
			earliest = coder;
	}
	if (!earliest)
	{
		deactivate_simulation(data);
		return (ULONG_MAX);
	}
	if (now >= earliest->deadline)
	{
		emit_state(earliest, "burned out", now);
		deactivate_simulation(data);
	}
	return (earliest->deadline);
}

void	*monitor_thread(void *arg)
{
	t_data			*data;
	unsigned long	deadline;

	data = arg;
	pthread_mutex_lock(&data->simulation_mutex);
	while (data->is_active)
	{
		deadline = monitor_deadlines(data, current_microseconds());
		if (data->is_active)
			wait_for_change(data, deadline);
	}
	pthread_mutex_unlock(&data->simulation_mutex);
	return (NULL);
}
