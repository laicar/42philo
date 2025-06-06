/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor_routine.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clai-ton <clai-ton@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/06 11:15:46 by clai-ton          #+#    #+#             */
/*   Updated: 2025/06/06 14:57:17 by clai-ton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	should_routine_stop(t_monitor *monitor)
{
	pthread_mutex_lock(&monitor->flags_lock);
	if (monitor->dead_philo_flag || monitor->all_meals_flag)
	{
		pthread_mutex_unlock(&monitor->flags_lock);
		return (SIM_STOP);
	}
	pthread_mutex_unlock(&monitor->flags_lock);
	return (SIM_CONTINUE);
}

void	found_dead_philo(t_monitor *monitor, t_philo *dead_philo)
{
	philo_print(dead_philo, MSG_DYING);
	pthread_mutex_lock(&monitor->flags_lock);
	monitor->dead_philo_flag = B_TRUE;
	pthread_mutex_unlock(&monitor->flags_lock);
}

void	update_done_philos(t_monitor *monitor)
{
	pthread_mutex_lock(&monitor->philo_done_lock);
	++monitor->philo_done_nb;
	if (monitor->philo_done_nb >= monitor->philo_nb)
	{
		pthread_mutex_lock(&monitor->flags_lock);
		monitor->all_meals_flag = B_TRUE;
		pthread_mutex_unlock(&monitor->flags_lock);
	}
	pthread_mutex_unlock(&monitor->philo_done_lock);
}

void	*monitor_routine(void *void_monitor)
{
	t_monitor	*monitor;
	int			continue_sim;
	int			i;
	size_t		philo_death_utime;

	monitor = (t_monitor *) void_monitor;
	continue_sim = SIM_CONTINUE;
	wait_for_start_time(monitor->start_utime);
	i = 0;
	while (continue_sim == SIM_CONTINUE)
	{
		continue_sim = should_routine_stop(monitor);
		pthread_mutex_lock(&monitor->philos[i].death_time_lock);
		philo_death_utime = monitor->philos[i].will_die_utime;
		pthread_mutex_unlock(&monitor->philos[i].death_time_lock);
		if (philo_death_utime < ft_get_utime())
		{
			found_dead_philo(monitor, &monitor->philos[i]);
			continue_sim = SIM_STOP;
		}
		++i;
		if (i == monitor->philo_nb)
			i = 0;
	}
	return (NULL);
}