/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pair_ready.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crodrigo <crodrigo@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/18 21:01:06 by crodrigo          #+#    #+#             */
/*   Updated: 2026/11/18 21:01:06 by crodrigo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

unsigned long	next_pair_ready_time(t_coder *coder)
{
	t_dongle		*first;
	t_dongle		*second;
	unsigned long	ready_at;

	first = coder->first_dongle;
	second = coder->second_dongle;
	if (first == second || first->in_use || second->in_use)
		return (ULONG_MAX);
	ready_at = first->available_at;
	if (second->available_at > ready_at)
		ready_at = second->available_at;
	if (coder->stagger_ready_at > ready_at)
		ready_at = coder->stagger_ready_at;
	return (ready_at);
}
