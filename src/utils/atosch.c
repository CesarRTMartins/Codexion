/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   atosch.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crodrigo <crodrigo@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/18 21:02:27 by crodrigo          #+#    #+#             */
/*   Updated: 2026/11/18 21:02:27 by crodrigo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

static char	*lower(const char *s)
{
	char	*res;
	int		i;

	res = malloc(ft_strlen(s) + 1);
	if (!res)
		return (NULL);
	i = 0;
	while (s[i])
	{
		res[i] = s[i];
		if (s[i] >= 'A' && s[i] <= 'Z')
			res[i] = s[i] + 32;
		i++;
	}
	res[i] = '\0';
	return (res);
}

t_scheduler	ft_atosch(const char *nptr)
{
	char	*low;

	low = lower(nptr);
	if (low && ft_strcmp(low, "fifo") == 0)
		return (free(low), FIFO);
	if (low && ft_strcmp(low, "edf") == 0)
		return (free(low), EDF);
	free(low);
	return (error("Scheduler value must be one of: FIFO, EDF"));
}
