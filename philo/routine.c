/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clai-ton <clai-ton@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 16:00:52 by clai-ton          #+#    #+#             */
/*   Updated: 2025/06/04 17:59:02 by clai-ton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	should_stop_routine(t_monitor *monitor)
{
	pthread_mutex_lock(&monitor->lock);
	if (monitor->all_meals_flag || monitor->dead_philo_flag)
	{
		pthread_mutex_unlock(&monitor->lock);
		return (B_TRUE);
	}
	pthread_mutex_unlock(&monitor->lock);
	return (B_FALSE);
}

/*
The even-numbered philosophers will start their routine with a delay
to avoid conflicts.
*/
void	*philo_routine(void *data)
{
	t_philo	*philo;

	philo = (t_philo *) data;
	if (philo->id_nb % 2 == 0)
		ft_usleep(10);
	//todo
	return (NULL);
}