/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   codexion.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crodrigo <crodrigo@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/18 21:00:26 by crodrigo          #+#    #+#             */
/*   Updated: 2026/11/18 21:00:26 by crodrigo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CODEXION_H
# define CODEXION_H

# include <limits.h>
# include <time.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include "struct.h"

void			initialize_simulation(t_data *data);
void			allocate_coders(t_data *data);
void			seed_wait_queue(t_data *data);
void			allocate_dongles(t_data *data);
void			parse_simulation_args(int ac, char **av, t_data *data);

void			*coder_thread(void *arg);
void			*monitor_thread(void *arg);
unsigned long	monitor_deadlines(t_data *data, unsigned long now);
void			deactivate_simulation(t_data *data);

int				acquire_dongles(t_coder *coder);
void			return_dongles(t_coder *coder, unsigned long now);
unsigned long	next_pair_ready_time(t_coder *coder);
int				compare_requests(t_scheduler policy, t_request *a,
					t_request *b);
void			join_wait_queue(t_coder *coder);
void			leave_wait_queue(t_data *data, t_request *request);
int				owns_wait_priority(t_data *data, t_request *request);

unsigned int	ft_atoui(const char *nptr);
t_scheduler		ft_atosch(const char *nptr);
int				ft_strcmp(const char *s1, const char *s2);
size_t			ft_strlen(const char *s);
void			emit_state(t_coder *coder, const char *action,
					unsigned long now);
int				error(const char *msg);
int				ft_isnumber(const char *str);
void			cleanup(t_data *data);
unsigned long	current_microseconds(void);
void			wait_for_change(t_data *data, unsigned long until);
void			sleep_until(t_data *data, unsigned long until);

#endif
