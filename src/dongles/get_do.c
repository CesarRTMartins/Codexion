/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_do.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crodrigo <crodrigo@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/18 21:00:56 by crodrigo          #+#    #+#             */
/*   Updated: 2026/11/18 21:00:56 by crodrigo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

static int	wait_for_pair(t_coder *coder)
{
	t_data			*data;
	unsigned long	now;
	unsigned long	ready_at;

	data = coder->data;
	while (data->is_active)
	{
		now = current_microseconds();
		monitor_deadlines(data, now);
		if (!data->is_active)
			break ;
		ready_at = next_pair_ready_time(coder);
		if (ready_at <= now && owns_wait_priority(data, &coder->request))
			return (1);
		if (ready_at <= now)
			ready_at = ULONG_MAX;
		wait_for_change(data, ready_at);
	}
	return (0);
}

int	acquire_dongles(t_coder *coder)
{
	t_data		*data;
	int			granted;

	data = coder->data;
	if (coder->completed_compile_count > 0)
		join_wait_queue(coder);
	granted = wait_for_pair(coder);
	leave_wait_queue(data, &coder->request);
	if (granted)
	{
		coder->first_dongle->in_use = true;
		coder->second_dongle->in_use = true;
	}
	return (granted);
}
