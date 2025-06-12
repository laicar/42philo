/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor_routine.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clai-ton <clai-ton@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/06 11:15:46 by clai-ton          #+#    #+#             */
/*   Updated: 2025/06/12 15:45:27 by clai-ton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	should_routine_stop(t_monitor *monitor)
{
	pthread_mutex_lock(&monitor->flags_lock);
	if (monitor->dead_philo_flag == B_TRUE || monitor->all_meals_flag == B_TRUE)
	{
		pthread_mutex_unlock(&monitor->flags_lock);
		return (SIM_STOP);
	}
	pthread_mutex_unlock(&monitor->flags_lock);
	return (SIM_CONTINUE);
}

void	found_dead_philo(t_monitor *monitor, t_philo *dead_philo)
{
	pthread_mutex_lock(&monitor->flags_lock);
	monitor->dead_philo_flag = B_TRUE;
	pthread_mutex_unlock(&monitor->flags_lock);
	pthread_mutex_lock(&monitor->write_lock);
	printf("%lu %d %s\n", mtime_diff(monitor->start_utime, ft_get_utime()),
		dead_philo->id_nb, MSG_DYING);
	pthread_mutex_unlock(&monitor->write_lock);
}

void	update_done_philos(t_monitor *monitor)
{
	pthread_mutex_lock(&monitor->philo_done_lock);
	++monitor->philo_done_nb;
	if (monitor->philo_done_nb == monitor->philo_nb)
	{
		pthread_mutex_unlock(&monitor->philo_done_lock);
		pthread_mutex_lock(&monitor->flags_lock);
		monitor->all_meals_flag = B_TRUE;
		pthread_mutex_unlock(&monitor->flags_lock);
	}
	else
		pthread_mutex_unlock(&monitor->philo_done_lock);
}

static void	monitor_loop(t_monitor *monitor)
{
	int			i;
	size_t		philo_death_mtime;

	i = 0;
	if (monitor->philo_nb == 1)
		ft_usleep(monitor->utime_to_die);
	while (1)
	{
		if (should_routine_stop(monitor) == SIM_STOP)
			break ;
		pthread_mutex_lock(&monitor->philos[i].death_time_lock);
		philo_death_mtime = monitor->philos[i].will_die_mtime;
		pthread_mutex_unlock(&monitor->philos[i].death_time_lock);
		if (philo_death_mtime < ft_get_mtime())
		{
			found_dead_philo(monitor, &monitor->philos[i]);
			break ;
		}
		++i;
		if (i == monitor->philo_nb)
			i = 0;
	}
}

void	*monitor_routine(void *void_monitor)
{
	t_monitor	*monitor;

	monitor = (t_monitor *) void_monitor;
	if (monitor->meal_target_nb == 0)
		return (NULL);
	wait_for_start_time(monitor->start_utime);
	monitor_loop(monitor);
	return (NULL);
}
