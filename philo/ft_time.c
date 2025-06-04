/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_time.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clai-ton <clai-ton@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 18:02:06 by clai-ton          #+#    #+#             */
/*   Updated: 2025/06/04 13:12:33 by clai-ton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

size_t	ft_get_mtime(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000UL + tv.tv_usec / 1000UL);
}

size_t	ft_get_utime(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000000UL + tv.tv_usec);
}

/*
A more precise usleep using gettimeofday().
Has the inconvenience of using up more CPU.
*/
void	ft_usleep(size_t useconds)
{
	size_t	start;
	size_t	current;
	size_t	elapsed;
	size_t	remaining;

	start = ft_get_utime();
	elapsed = 0;
	remaining = useconds;
	while (elapsed < useconds)
	{
		if (remaining > 200)
			usleep(remaining >> 1);
		current = ft_get_utime();
		elapsed = current - start;
		remaining = useconds - elapsed;
	}
}
