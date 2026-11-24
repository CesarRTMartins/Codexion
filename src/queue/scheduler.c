/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scheduler.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crodrigo <crodrigo@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/18 21:02:03 by crodrigo          #+#    #+#             */
/*   Updated: 2026/11/18 21:02:03 by crodrigo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

int	compare_requests(t_scheduler policy, t_request *a, t_request *b)
{
	if (policy == EDF && a->deadline != b->deadline)
		return (a->deadline < b->deadline);
	return (a->arrival_order < b->arrival_order);
}
