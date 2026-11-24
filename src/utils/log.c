/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   log.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crodrigo <crodrigo@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/18 21:02:52 by crodrigo          #+#    #+#             */
/*   Updated: 2026/11/18 21:02:52 by crodrigo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

void	emit_state(t_coder *coder, const char *action, unsigned long now)
{
	printf("%lu %u %s\n", (now - coder->data->simulation_start) / 1000UL,
		coder->coder_number, action);
}
