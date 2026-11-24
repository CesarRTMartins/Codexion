/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crodrigo <crodrigo@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/18 21:03:07 by crodrigo          #+#    #+#             */
/*   Updated: 2026/11/18 21:03:07 by crodrigo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

unsigned long	current_microseconds(void)
{
	struct timespec	ts;

	clock_gettime(CLOCK_MONOTONIC, &ts);
	return (ts.tv_sec * 1000000UL + ts.tv_nsec / 1000UL);
}

void	wait_for_change(t_data *data, unsigned long until)
{
	struct timespec	wakeup;
	unsigned long	now;
	unsigned long	remaining;

	if (until == ULONG_MAX)
	{
		pthread_cond_wait(&data->state_changed, &data->simulation_mutex);
		return ;
	}
	now = current_microseconds();
	if (now >= until)
		return ;
	remaining = until - now;
	clock_gettime(CLOCK_REALTIME, &wakeup);
	wakeup.tv_sec += remaining / 1000000UL;
	wakeup.tv_nsec += (remaining % 1000000UL) * 1000UL;
	wakeup.tv_sec += wakeup.tv_nsec / 1000000000L;
	wakeup.tv_nsec %= 1000000000L;
	pthread_cond_timedwait(&data->state_changed, &data->simulation_mutex,
		&wakeup);
}

void	sleep_until(t_data *data, unsigned long until)
{
	while (data->is_active && current_microseconds() < until)
		wait_for_change(data, until);
}
