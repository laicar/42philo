/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clai-ton <clai-ton@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/06 13:32:59 by clai-ton          #+#    #+#             */
/*   Updated: 2025/06/12 16:34:12 by clai-ton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static void	*lone_philo_case(t_philo *philo)
{
	wait_for_start_time(philo->monitor->start_utime);
	pthread_mutex_lock(&philo->own_fork);
	philo_print(philo, MSG_TAKE_FORK);
	ft_usleep(philo->monitor->utime_to_die);
	pthread_mutex_unlock(&philo->own_fork);
	return (NULL);
}

static int	philo_sleep_think(t_philo *philo)
{
	if (should_routine_stop(philo->monitor) == SIM_STOP)
		return (SIM_STOP);
	philo_print(philo, MSG_SLEEPING);
	ft_usleep(philo->monitor->utime_to_sleep);
	if (should_routine_stop(philo->monitor) == SIM_STOP)
		return (SIM_STOP);
	philo_print(philo, MSG_THINKING);
	return (SIM_CONTINUE);
}

static int	philo_eat(t_philo *philo)
{
	size_t	ttd;

	if (should_routine_stop(philo->monitor) == SIM_STOP)
		return (SIM_STOP);
	ttd = 5 + philo->monitor->utime_to_die / 1000;
	pthread_mutex_lock(philo->fork1);
	philo_print(philo, MSG_TAKE_FORK);
	pthread_mutex_lock(philo->fork2);
	philo_print(philo, MSG_TAKE_FORK);
	pthread_mutex_lock(&philo->death_time_lock);
	philo->will_die_mtime = ft_get_mtime() + ttd;
	pthread_mutex_unlock(&philo->death_time_lock);
	philo_print(philo, MSG_EATING);
	ft_usleep(philo->monitor->utime_to_eat);
	pthread_mutex_unlock(philo->fork2);
	pthread_mutex_unlock(philo->fork1);
	++philo->meals_eaten_nb;
	if (philo->monitor->meal_target_nb != DFL_MEALS
		&& philo->meals_eaten_nb == philo->monitor->meal_target_nb)
		update_done_philos(philo->monitor);
	return (SIM_CONTINUE);
}

/*
The even-numbered philosophers will start their routine with a delay
to avoid conflicts.
*/
void	*philo_routine(void *void_philo)
{
	t_philo	*philo;

	philo = (t_philo *) void_philo;
	if (philo->monitor->meal_target_nb == 0)
		return (NULL);
	if (philo->monitor->philo_nb == 1)
		return (lone_philo_case(philo));
	wait_for_start_time(philo->monitor->start_utime);
	if (philo->id_nb % 2)
	{
		philo_print(philo, MSG_THINKING);
		ft_usleep(philo->monitor->utime_to_eat >> 1);
	}
	while (1)
	{
		if (philo_eat(philo) == SIM_STOP)
			break ;
		if (philo_sleep_think(philo) == SIM_STOP)
			break ;
	}
	return (NULL);
}
