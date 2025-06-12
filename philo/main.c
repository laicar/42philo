/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clai-ton <clai-ton@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 19:45:59 by clai-ton          #+#    #+#             */
/*   Updated: 2025/06/12 15:22:27 by clai-ton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

// number_of_philosophers time_to_die time_to_eat time_to_sleep
// [number_of_times_each_philosopher_must_eat]
int	main(int argc, char **argv)
{
	t_monitor	*monitor;
	int			i;

	monitor = init_project(argc, argv);
	if (pthread_create(&monitor->thread, NULL, monitor_routine, monitor))
		ft_exit_free_data(monitor, "Error when creating threads.\n");
	i = 0;
	while (i < monitor->philo_nb)
	{
		if (pthread_create(&monitor->philos[i].thread, NULL,
				philo_routine, &monitor->philos[i]))
			ft_exit_free_data(monitor, "Error when creating threads.\n");
		++i;
	}
	i = 0;
	while (i < monitor->philo_nb)
		pthread_join(monitor->philos[i++].thread, NULL);
	pthread_join(monitor->thread, NULL);
	ft_free_data(monitor);
	return (EXIT_SUCCESS);
}
