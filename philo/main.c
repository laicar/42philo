/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clai-ton <clai-ton@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 19:45:59 by clai-ton          #+#    #+#             */
/*   Updated: 2025/01/09 17:07:53 by clai-ton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	main(int argc, char **argv)
{
	if (argc < 5 || argc > 6)
	{
		printf("Wrong usage. Do:\n./philo number_of_philosophers "
			"time_to_die time_to_eat time_to_sleep "
			"[optional: number_of_times_each_philosopher_must_eat]\n");
		return (EXIT_SUCCESS);
	}
	
	return (EXIT_SUCCESS);
}