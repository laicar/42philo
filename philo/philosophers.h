/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clai-ton <clai-ton@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 17:42:17 by clai-ton          #+#    #+#             */
/*   Updated: 2025/06/06 13:17:37 by clai-ton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <pthread.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>
# include <stdio.h>

// The official output specified

# define MSG_TAKE_FORK "has taken a fork"
# define MSG_THINKING "is thinking"
# define MSG_SLEEPING "is sleeping"
# define MSG_EATING "is eating"
# define MSG_DYING "died"

// Booleans
# define B_TRUE 1
# define B_FALSE 0

# define SIM_CONTINUE 1
# define SIM_STOP 0

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
	int					meals_eaten_nb;
	size_t				will_die_utime;
	pthread_mutex_t 	l_fork;
	pthread_mutex_t		*r_fork;
	pthread_mutex_t 	death_time_lock;
}	t_philo;

typedef struct s_monitor
{
	t_philo			philos[P_MAX];
	int				philo_nb;
	size_t			start_utime;
	int				utime_to_die;
	int				utime_to_eat;
	int				utime_to_sleep;
	int				meal_target_nb;
	int				dead_philo_flag;
	int				all_meals_flag;
	int				philo_done_nb;
	pthread_t		thread;
	pthread_mutex_t	flags_lock;
	pthread_mutex_t	philo_done_lock;
	pthread_mutex_t	write_lock;
} t_monitor;

size_t		ft_get_utime(void);
size_t		mtime_diff(size_t start_utime, size_t end_utime);
void		ft_usleep(size_t useconds);
void		wait_for_start_time(size_t start_utime);

int			ft_parse_arg(char *str);
t_monitor	*init_project(int argc, char **argv);

int			philo_print(t_philo *philo, char *action_msg);
void		*philo_routine(void *void_philo);

void		*monitor_routine(void *void_monitor);
int			should_routine_stop(t_monitor *monitor);
void		found_dead_philo(t_monitor *monitor, t_philo *dead_philo);
void		update_done_philos(t_monitor *monitor);

void		ft_free_data(t_monitor *monitor);
void		ft_exit_error(char *message);
void		ft_exit_free_data(t_monitor *monitor, char *message);
#endif