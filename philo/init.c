/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clai-ton <clai-ton@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 12:40:44 by clai-ton          #+#    #+#             */
/*   Updated: 2025/06/04 17:58:49 by clai-ton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static void	init_philo(t_monitor *monitor, int nb_philo)
{
	int	i;

	i = 0;
	while (i < nb_philo)
	{
		monitor->philos[i].monitor = monitor;
		monitor->philos[i].last_meal_start_utime = monitor->start_utime;
		monitor->philos[i].id_nb = i + 1;
		monitor->philos[i].meals_eaten_nb = 0;
		pthread_mutex_init(&monitor->philos[i].l_fork, NULL);
		pthread_mutex_init(&monitor->philos[i].state_lock, NULL);
		++i;
	}
	monitor->philos[0].r_fork = monitor->philos[nb_philo - 1].l_fork;
	i = 1;
	while (i < nb_philo)
	{
		monitor->philos[i].r_fork = monitor->philos[i - 1].l_fork;
		++i;
	}
}

static int	init_monitor_arg(int argc, char **argv, t_monitor *monitor)
{
	monitor->philo_nb = ft_parse_arg(argv[1]);
	monitor->mtime_to_die = ft_parse_arg(argv[2]);
	monitor->mtime_to_eat = ft_parse_arg(argv[3]);
	monitor->mtime_to_sleep = ft_parse_arg(argv[4]);
	if (argc == 6)
		monitor->meal_target_nb = ft_parse_arg(argv[5]);
	else
		monitor->meal_target_nb = -2;
	if (monitor->meal_target_nb == -1 || monitor->mtime_to_die == -1
		|| monitor->mtime_to_eat == -1 || monitor->mtime_to_sleep == -1
		|| monitor->philo_nb == -1 || monitor->philo_nb > P_MAX)
	{
		free(monitor);
		printf("Argument error."
			" All arguments must be positive numbers"
			" and philo max number is %i.\n"
			, P_MAX);
		exit(EXIT_FAILURE);
	}
	return (0);
}

static t_monitor	*init_monitor(int argc, char **argv)
{
	t_monitor	*monitor;

	monitor = (t_monitor *) malloc(sizeof(t_monitor));
	if (!monitor || init_monitor_arg(argc, argv, monitor))
		return (NULL);
	monitor->dead_philo_flag = 0;
	monitor->all_meals_flag = 0;
	monitor->philo_done_nb = 0;
	pthread_mutex_init(&monitor->lock, NULL);
	monitor->start_utime = ft_get_utime();
	return (monitor);
}

t_monitor	*init_project(int argc, char **argv)
{
	t_monitor	*monitor;

	if (argc < 5 || argc > 6)
	{
		printf("Wrong usage. Do:\n./philo number_of_philosophers "
			"time_to_die time_to_eat time_to_sleep "
			"[optional: number_of_times_each_philosopher_must_eat]\n");
		exit(EXIT_SUCCESS);
	}
	monitor = init_monitor(argc, argv);
	if (!monitor)
	{
		printf("Malloc error.\n");
		exit(EXIT_FAILURE);
	}
	init_philo(monitor, monitor->philo_nb);
	return (monitor);
}
