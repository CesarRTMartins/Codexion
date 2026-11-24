/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   atoui.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crodrigo <crodrigo@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/18 21:02:32 by crodrigo          #+#    #+#             */
/*   Updated: 2026/11/18 21:02:32 by crodrigo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

unsigned int	ft_atoui(const char *nptr)
{
	unsigned int	res;
	unsigned int	digit;

	res = 0;
	while (*nptr >= '0' && *nptr <= '9')
	{
		digit = *nptr++ - '0';
		if (res > (UINT_MAX - digit) / 10)
			error("Numeric argument exceeds the supported range.");
		res = res * 10 + digit;
	}
	return (res);
}
