/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crodrigo <crodrigo@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/18 21:00:37 by crodrigo          #+#    #+#             */
/*   Updated: 2026/11/18 21:00:37 by crodrigo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_H
# define STRUCT_H

# include <pthread.h>
# include <stdbool.h>

typedef enum e_scheduler
{
	FIFO,
	EDF,
}	t_scheduler;

typedef struct s_request
{
	struct s_coder		*coder;
	unsigned long		deadline;
	unsigned long		arrival_order;
	struct s_request	*next;
}	t_request;

typedef struct s_dongle
{
	bool			in_use;
	unsigned long	available_at;
}	t_dongle;

typedef struct s_coder
{
	unsigned int	coder_number;
	unsigned int	completed_compile_count;
	unsigned long	deadline;
	unsigned long	stagger_ready_at;
	t_dongle		*first_dongle;
	t_dongle		*second_dongle;
	t_request		request;
	pthread_t		thread;
	struct s_data	*data;
}	t_coder;

typedef struct s_data
{
	unsigned int	coder_count;
	unsigned int	burnout_limit_ms;
	unsigned int	compile_duration_ms;
	unsigned int	debug_duration_ms;
	unsigned int	refactor_duration_ms;
	unsigned int	required_compile_count;
	unsigned int	dongle_recovery_ms;
	t_scheduler		scheduling_policy;
	t_coder			*coder_table;
	t_dongle		*dongle_table;
	pthread_mutex_t	simulation_mutex;
	pthread_cond_t	state_changed;
	bool			is_active;
	unsigned long	simulation_start;
	unsigned int	completed_coder_count;
	unsigned long	next_request_order;
	t_request		*wait_queue;
}	t_data;

#endif
