/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clai-ton <clai-ton@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 12:40:44 by clai-ton          #+#    #+#             */
/*   Updated: 2025/06/12 16:22:02 by clai-ton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static void	init_forks(t_monitor *monitor, int nb_philo)
{
	int	i;

	monitor->philos[0].fork1 = &(monitor->philos[0].own_fork);
	monitor->philos[0].fork2 = &(monitor->philos[nb_philo - 1].own_fork);
	i = 1;
	while (i < nb_philo)
	{
		if (i % 2)
		{
			monitor->philos[i].fork1 = &(monitor->philos[i - 1].own_fork);
			monitor->philos[i].fork2 = &(monitor->philos[i].own_fork);
		}
		else
		{
			monitor->philos[i].fork2 = &(monitor->philos[i - 1].own_fork);
			monitor->philos[i].fork1 = &(monitor->philos[i].own_fork);
		}
		++i;
	}
}

static void	init_philo(t_monitor *monitor, int nb_philo)
{
	int		i;
	size_t	ttd;

	i = 0;
	ttd = (monitor->start_utime + monitor->utime_to_die) / 1000;
	while (i < nb_philo)
	{
		monitor->philos[i].monitor = monitor;
		monitor->philos[i].will_die_mtime = ttd;
		monitor->philos[i].id_nb = i + 1;
		monitor->philos[i].meals_eaten_nb = 0;
		pthread_mutex_init(&monitor->philos[i].own_fork, NULL);
		pthread_mutex_init(&monitor->philos[i].death_time_lock, NULL);
		++i;
	}
	init_forks(monitor, nb_philo);
}

static int	init_monitor_arg(int argc, char **argv, t_monitor *monitor)
{
	monitor->philo_nb = ft_parse_arg(argv[1]);
	monitor->utime_to_die = ft_parse_arg(argv[2]);
	monitor->utime_to_eat = ft_parse_arg(argv[3]);
	monitor->utime_to_sleep = ft_parse_arg(argv[4]);
	if (argc == 6)
		monitor->meal_target_nb = ft_parse_arg(argv[5]);
	else
		monitor->meal_target_nb = DFL_MEALS;
	if (monitor->meal_target_nb == -1 || monitor->utime_to_die == -1
		|| monitor->utime_to_eat == -1 || monitor->utime_to_sleep == -1
		|| monitor->philo_nb <= 0 || monitor->philo_nb > P_MAX)
	{
		free(monitor);
		printf("Argument error.\n"
			"All arguments must be positive integers,"
			" there must be at least 1 philo, and philo max number is %i.\n",
			P_MAX);
		exit(EXIT_FAILURE);
	}
	monitor->utime_to_die *= 1000;
	monitor->utime_to_eat *= 1000;
	monitor->utime_to_sleep *= 1000;
	return (0);
}

static t_monitor	*init_monitor(int argc, char **argv)
{
	t_monitor	*monitor;

	monitor = (t_monitor *) malloc(sizeof(t_monitor));
	if (!monitor || init_monitor_arg(argc, argv, monitor))
		return (NULL);
	monitor->dead_philo_flag = B_FALSE;
	monitor->all_meals_flag = B_FALSE;
	monitor->philo_done_nb = 0;
	pthread_mutex_init(&monitor->flags_lock, NULL);
	pthread_mutex_init(&monitor->philo_done_lock, NULL);
	pthread_mutex_init(&monitor->write_lock, NULL);
	monitor->start_utime = ft_get_utime() + (monitor->philo_nb * 40000);
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
