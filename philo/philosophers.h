/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clai-ton <clai-ton@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 17:42:17 by clai-ton          #+#    #+#             */
/*   Updated: 2025/05/30 15:04:23 by clai-ton         ###   ########.fr       */
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
	PHILO_START
};

// The official output specified
# define P_TAKE_FORK "has taken a fork"
# define P_THINKING "is thinking"
# define P_SLEEPING "is sleeping"
# define P_EATING "is eating"
# define P_DEAD "died"

typedef struct s_philosopher
{
	t_monitor		*monitor;
	pthread_t		thread;
	int				id_nb;
	int				state_enum;
	int				meals_eaten_nb;
	size_t			last_meal_utime;
	pthread_mutex_t	r_fork;
	pthread_mutex_t l_fork;
}	t_philo;

typedef struct s_monitor
{
	t_philo			*philos;
	int				philo_count;
	size_t			start_utime;
	int				mtime_to_die;
	int				mtime_to_eat;
	int				mtime_to_sleep;
	int				meal_target_nb;
	pthread_mutex_t	write_lock;
	int				dead_philo_flag;
} t_monitor;


size_t	ft_get_utime(void);
void	ft_usleep(size_t useconds);
void	ft_philo_print();

#endif