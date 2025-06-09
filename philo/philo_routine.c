/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clai-ton <clai-ton@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/06 13:32:59 by clai-ton          #+#    #+#             */
/*   Updated: 2025/06/06 15:14:13 by clai-ton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static void	*lone_philo_case(t_philo *philo)
{
	pthread_mutex_lock(&philo->l_fork);
	philo_print(philo, MSG_TAKE_FORK);
	ft_usleep(philo->monitor->utime_to_die);
	pthread_mutex_unlock(&philo->l_fork);
	found_dead_philo(philo->monitor, philo);
	should_routine_stop(philo->monitor);
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
	if (should_routine_stop(philo->monitor) == SIM_STOP)
		return (SIM_STOP);
	pthread_mutex_lock(&philo->l_fork);
	philo_print(philo, MSG_TAKE_FORK);
	pthread_mutex_lock(philo->r_fork);
	philo_print(philo, MSG_TAKE_FORK);
	pthread_mutex_lock(&philo->death_time_lock);
	philo->will_die_utime =
		ft_get_utime() + philo->monitor->utime_to_die;
	pthread_mutex_unlock(&philo->death_time_lock);
	philo_print(philo, MSG_EATING);
	ft_usleep(philo->monitor->utime_to_eat);
	pthread_mutex_unlock(&philo->l_fork);
	pthread_mutex_unlock(philo->r_fork);
	++philo->meals_eaten_nb;
	if (philo->monitor->meal_target_nb != DFL_MEALS
		&& philo->meals_eaten_nb == philo->monitor->meal_target_nb)
		update_done_philos(philo->monitor);
	if (should_routine_stop(philo->monitor) == SIM_STOP)
		return (SIM_STOP);
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
		ft_usleep(philo->monitor->utime_to_eat >> 1);
	while (1)
	{
		if (philo_eat(philo) == SIM_STOP)
			break;
		if (philo_sleep_think(philo) == SIM_STOP)
			break; 
	}
	return (NULL);
}
