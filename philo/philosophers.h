/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clai-ton <clai-ton@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 17:42:17 by clai-ton          #+#    #+#             */
/*   Updated: 2025/06/04 17:58:03 by clai-ton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <pthread.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>
# include <stdio.h>

//TODO see if used
enum e_philo_state
{
	PHILO_EATING,
	PHILO_SLEEPING,
	PHILO_THINKING,
	PHILO_TAKE_FORK_1,
	PHILO_DEAD,
	PHILO_FINISHED,
	PHILO_START
};

// The official output specified

# define P_TAKE_FORK "has taken a fork"
# define P_THINKING "is thinking"
# define P_SLEEPING "is sleeping"
# define P_EATING "is eating"
# define P_DYING "died"

// Booleans
# define B_TRUE 1
# define B_FALSE 0

// The maximum number of philosophers in a simulation during evaluation
# define P_MAX 200
// The default value for no meal number target
# define DFL_MEALS -42

struct s_monitor;

typedef struct s_philosopher
{
	struct s_monitor	*monitor;
	pthread_t			thread;
	int					id_nb;
	int					state_enum;
	int					meals_eaten_nb;
	size_t				last_meal_start_utime;
	pthread_mutex_t		r_fork;
	pthread_mutex_t 	l_fork;
	pthread_mutex_t 	state_lock;
}	t_philo;

typedef struct s_monitor
{
	t_philo			philos[P_MAX];
	int				philo_nb;
	size_t			start_utime;
	int				mtime_to_die;
	int				mtime_to_eat;
	int				mtime_to_sleep;
	int				meal_target_nb;
	pthread_mutex_t	flags_lock;
	pthread_mutex_t	write_lock;
	int				dead_philo_flag;
	int				all_meals_flag;
	int				philo_done_nb;
} t_monitor;

int			ft_parse_arg(char *str);
t_monitor	*init_project(int argc, char **argv);
size_t		ft_get_utime(void);
void		ft_usleep(size_t useconds);
void		ft_philo_print();
void		*philo_routine(void *data);
void		ft_free_data(t_monitor *monitor);
void		ft_exit_error(char *message);
void		ft_exit_free_data(t_monitor *monitor, char *message);
#endif