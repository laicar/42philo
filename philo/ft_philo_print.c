/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_philo_print.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clai-ton <clai-ton@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 17:47:03 by clai-ton          #+#    #+#             */
/*   Updated: 2025/01/06 19:39:05 by clai-ton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	ft_philo_print(unsigned long time, int philo, char *str)
{
	//lock write mutex
	printf("%lu %d %s\n", time, philo, str);
	//unlock write mutex
}