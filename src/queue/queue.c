/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   queue.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crodrigo <crodrigo@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/18 21:01:57 by crodrigo          #+#    #+#             */
/*   Updated: 2026/11/18 21:01:57 by crodrigo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

void	join_wait_queue(t_coder *coder)
{
	t_data		*data;
	t_request	*request;
	t_request	**entry;

	data = coder->data;
	request = &coder->request;
	*request = (t_request){coder, coder->deadline,
		data->next_request_order++, NULL};
	entry = &data->wait_queue;
	while (*entry && compare_requests(data->scheduling_policy, *entry, request))
		entry = &(*entry)->next;
	request->next = *entry;
	*entry = request;
}

void	leave_wait_queue(t_data *data, t_request *request)
{
	t_request	**entry;

	entry = &data->wait_queue;
	while (*entry != request)
		entry = &(*entry)->next;
	*entry = request->next;
}

static int	shares_dongle(t_coder *a, t_coder *b)
{
	return (a->first_dongle == b->first_dongle
		|| a->first_dongle == b->second_dongle
		|| a->second_dongle == b->first_dongle
		|| a->second_dongle == b->second_dongle);
}

int	owns_wait_priority(t_data *data, t_request *request)
{
	t_request	*entry;

	entry = data->wait_queue;
	while (entry != request)
	{
		if (shares_dongle(entry->coder, request->coder))
			return (0);
		entry = entry->next;
	}
	return (1);
}
