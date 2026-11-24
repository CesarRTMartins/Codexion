/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crodrigo <crodrigo@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/18 21:02:42 by crodrigo          #+#    #+#             */
/*   Updated: 2026/11/18 21:02:42 by crodrigo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

int	error(const char *msg)
{
	if (msg)
	{
		write(STDERR_FILENO, "Error: ", 7);
		write(STDERR_FILENO, msg, ft_strlen(msg));
	}
	write(STDERR_FILENO, "\n", 1);
	exit(EXIT_FAILURE);
}
