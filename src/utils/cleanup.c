/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crodrigo <crodrigo@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/18 21:02:37 by crodrigo          #+#    #+#             */
/*   Updated: 2026/11/18 21:02:37 by crodrigo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

void	cleanup(t_data *data)
{
	pthread_cond_destroy(&data->state_changed);
	pthread_mutex_destroy(&data->simulation_mutex);
	free(data->coder_table);
	free(data->dongle_table);
}
