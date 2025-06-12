/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit_free.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clai-ton <clai-ton@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 16:44:11 by clai-ton          #+#    #+#             */
/*   Updated: 2025/06/12 15:33:15 by clai-ton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

//todo
void	ft_free_data(t_monitor *monitor)
{
	int	i;

	i = 0;
	while (i < monitor->philo_nb)
	{
		pthread_mutex_destroy(&monitor->philos[i].death_time_lock);
		pthread_mutex_destroy(&monitor->philos[i].own_fork);
		++i;
	}
	pthread_mutex_destroy(&monitor->flags_lock);
	pthread_mutex_destroy(&monitor->write_lock);
	pthread_mutex_destroy(&monitor->philo_done_lock);
	free(monitor);
}

void	ft_exit_error(char *message)
{
	printf("%s", message);
	exit(EXIT_FAILURE);
}

void	ft_exit_free_data(t_monitor *monitor, char *message)
{
	ft_free_data(monitor);
	ft_exit_error(message);
}
