/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_philo_print.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clai-ton <clai-ton@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 17:47:03 by clai-ton          #+#    #+#             */
/*   Updated: 2025/06/04 17:14:47 by clai-ton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

/*
Returns B_TRUE if has printed, B_FALSE otherwise.
Does not print if the simulation is supposed to have stopped.
*/
int	philo_print(t_philo *philo, char *action_msg)
{
	pthread_mutex_lock(&philo->monitor->flags_lock);
	if (philo->monitor->all_meals_flag || philo->monitor->dead_philo_flag)
	{
		pthread_mutex_unlock(&philo->monitor->flags_lock);
		return (B_FALSE);
	}
	pthread_mutex_lock(&philo->monitor->write_lock);
	printf("%lu %d %s\n", (ft_get_utime() - philo->monitor->start_utime) / 1000,
		philo->id_nb, action_msg);
	pthread_mutex_unlock(&philo->monitor->write_lock);
	pthread_mutex_unlock(&philo->monitor->flags_lock);
	return (B_TRUE);
}