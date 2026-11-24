/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_dongles.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crodrigo <crodrigo@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/18 21:01:41 by crodrigo          #+#    #+#             */
/*   Updated: 2026/11/18 21:01:41 by crodrigo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

void	allocate_dongles(t_data *data)
{
	data->dongle_table = calloc(data->coder_count, sizeof(t_dongle));
	if (!data->dongle_table)
		error("Dongles allocation failed.");
}
