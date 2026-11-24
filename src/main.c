/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crodrigo <crodrigo@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/18 21:03:11 by crodrigo          #+#    #+#             */
/*   Updated: 2026/11/18 21:03:11 by crodrigo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

void	deactivate_simulation(t_data *data)
{
	data->is_active = false;
	pthread_cond_broadcast(&data->state_changed);
}

static unsigned int	start_workers(t_data *data)
{
	unsigned int	i;

	i = 0;
	while (i < data->coder_count)
	{
		if (pthread_create(&data->coder_table[i].thread, NULL, coder_thread,
				&data->coder_table[i]) != 0)
			break ;
		i++;
	}
	return (i);
}

static int	run_simulation(t_data *data)
{
	pthread_t		monitor;
	unsigned int	started;
	int				monitor_status;

	pthread_mutex_lock(&data->simulation_mutex);
	started = start_workers(data);
	data->simulation_start = current_microseconds();
	data->is_active = true;
	if (started == data->coder_count)
		seed_wait_queue(data);
	monitor_status = -1;
	if (started == data->coder_count)
		monitor_status = pthread_create(&monitor, NULL, monitor_thread, data);
	if (monitor_status != 0)
		deactivate_simulation(data);
	pthread_mutex_unlock(&data->simulation_mutex);
	if (monitor_status == 0)
		pthread_join(monitor, NULL);
	while (started > 0)
		pthread_join(data->coder_table[--started].thread, NULL);
	return (monitor_status);
}

int	main(int argc, char **argv)
{
	t_data	data;
	int		status;

	parse_simulation_args(argc, argv, &data);
	setvbuf(stdout, NULL, _IOLBF, 0);
	initialize_simulation(&data);
	status = run_simulation(&data);
	cleanup(&data);
	if (status != 0)
		return (error("Thread creation failed."));
	return (0);
}
