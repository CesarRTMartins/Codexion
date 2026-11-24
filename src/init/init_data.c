/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crodrigo <crodrigo@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/18 21:01:31 by crodrigo          #+#    #+#             */
/*   Updated: 2026/11/18 21:01:31 by crodrigo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

void	initialize_simulation(t_data *data)
{
	allocate_dongles(data);
	allocate_coders(data);
	if (pthread_mutex_init(&data->simulation_mutex, NULL) != 0)
	{
		free(data->coder_table);
		free(data->dongle_table);
		error("Simulation mutex initialization failed.");
	}
	if (pthread_cond_init(&data->state_changed, NULL) != 0)
	{
		pthread_mutex_destroy(&data->simulation_mutex);
		free(data->coder_table);
		free(data->dongle_table);
		error("Simulation condition initialization failed.");
	}
}
