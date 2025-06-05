/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clai-ton <clai-ton@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 19:45:59 by clai-ton          #+#    #+#             */
/*   Updated: 2025/06/04 17:59:16 by clai-ton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

// number_of_philosophers time_to_die time_to_eat time_to_sleep
// [number_of_times_each_philosopher_must_eat]

int	main (int argc, char **argv)
{
	t_monitor	*monitor;
	// int			i;

	printf("%lu\n", monitor->start_utime);
	monitor = init_project(argc, argv);
	printf("%i %i %i %i %i\n", monitor->philo_nb, monitor->mtime_to_die,
		monitor->mtime_to_eat, monitor->mtime_to_sleep, monitor->meal_target_nb);
	// i = 0;
	// while (i < monitor->philo_nb)
	// {
	// 	pthread_create(&monitor->philos[i].thread, NULL,
	// 		&philo_routine, &monitor->philos[i]);
	// 	++i;
	// }
	//todo
	printf("%lu\n", monitor->start_utime - ft_get_utime());
	ft_free_data(monitor);
	return (EXIT_SUCCESS);
}