/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crodrigo <crodrigo@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/18 21:01:49 by crodrigo          #+#    #+#             */
/*   Updated: 2026/11/18 21:01:49 by crodrigo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

static void	validate_numeric_arguments(int ac, char **av)
{
	int	i;

	if (ac != 9)
		error("Invalid argument count. Expected 8 arguments.");
	i = 1;
	while (i < 8)
	{
		if (!ft_isnumber(av[i]))
			error("The first 7 arguments must be unsigned integers.");
		i++;
	}
}

static void	assign_data(t_data *data, char **av)
{
	*data = (t_data){
		.coder_count = ft_atoui(av[1]),
		.burnout_limit_ms = ft_atoui(av[2]),
		.compile_duration_ms = ft_atoui(av[3]),
		.debug_duration_ms = ft_atoui(av[4]),
		.refactor_duration_ms = ft_atoui(av[5]),
		.required_compile_count = ft_atoui(av[6]),
		.dongle_recovery_ms = ft_atoui(av[7]),
		.scheduling_policy = ft_atosch(av[8]),
	};
}

void	parse_simulation_args(int ac, char **av, t_data *data)
{
	validate_numeric_arguments(ac, av);
	assign_data(data, av);
	if (!data->coder_count
		|| !data->burnout_limit_ms
		|| !data->compile_duration_ms
		|| !data->debug_duration_ms
		|| !data->refactor_duration_ms
		|| !data->required_compile_count)
		error("coder_count, burnout_limit_ms, compile_duration_ms, "
			"debug_duration_ms, refactor_duration_ms and "
			"required_compile_count must be greater than zero.");
}
