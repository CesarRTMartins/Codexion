/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_dong.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crodrigo <crodrigo@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/18 21:01:15 by crodrigo          #+#    #+#             */
/*   Updated: 2026/11/18 21:01:15 by crodrigo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

void	return_dongles(t_coder *coder, unsigned long now)
{
	unsigned long	available_at;

	available_at = now + coder->data->dongle_recovery_ms * 1000UL;
	coder->first_dongle->in_use = false;
	coder->first_dongle->available_at = available_at;
	coder->second_dongle->in_use = false;
	coder->second_dongle->available_at = available_at;
	pthread_cond_broadcast(&coder->data->state_changed);
}
