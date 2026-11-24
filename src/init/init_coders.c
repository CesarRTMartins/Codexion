/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_coders.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crodrigo <crodrigo@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/18 21:01:26 by crodrigo          #+#    #+#             */
/*   Updated: 2026/11/18 21:01:26 by crodrigo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

void	allocate_coders(t_data *data)
{
	unsigned int	i;

	data->coder_table = calloc(data->coder_count, sizeof(t_coder));
	if (!data->coder_table)
	{
		free(data->dongle_table);
		error("Coders allocation failed.");
	}
	i = 0;
	while (i < data->coder_count)
	{
		data->coder_table[i].coder_number = i + 1;
		data->coder_table[i].first_dongle = &data->dongle_table[i];
		data->coder_table[i].second_dongle
			= &data->dongle_table[(i + 1) % data->coder_count];
		data->coder_table[i].data = data;
		i++;
	}
}

static unsigned long	start_spacing(t_data *data)
{
	unsigned long	turn;
	unsigned long	slots;
	unsigned long	spacing;
	unsigned long	burnout;
	unsigned long	cycle;

	if (data->coder_count < 5 || data->coder_count % 2 == 0)
		return (0);
	slots = data->coder_count / 2;
	turn = (data->compile_duration_ms
			+ (unsigned long)data->dongle_recovery_ms) * 1000UL;
	spacing = (turn + slots - 1) / slots;
	burnout = data->burnout_limit_ms * 1000UL;
	cycle = (data->compile_duration_ms + (unsigned long)data->debug_duration_ms
			+ data->refactor_duration_ms) * 1000UL;
	if (spacing * data->coder_count >= burnout || burnout > 3 * turn
		|| cycle > spacing * data->coder_count)
		return (0);
	return (spacing);
}

static void	enqueue_initial_waiter(t_data *data, t_coder *coder,
		unsigned long spacing)
{
	unsigned long	slot;

	coder->deadline = data->simulation_start + data->burnout_limit_ms * 1000UL;
	join_wait_queue(coder);
	slot = coder->request.arrival_order;
	coder->stagger_ready_at = data->simulation_start + spacing * slot;
}

void	seed_wait_queue(t_data *data)
{
	unsigned int	i;
	unsigned int	parity;
	unsigned long	spacing;

	spacing = start_spacing(data);
	parity = 0;
	while (parity < 2)
	{
		i = parity++;
		while (i < data->coder_count)
		{
			enqueue_initial_waiter(data, &data->coder_table[i], spacing);
			i += 2;
		}
	}
}
