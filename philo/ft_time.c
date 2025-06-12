/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_time.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clai-ton <clai-ton@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 18:02:06 by clai-ton          #+#    #+#             */
/*   Updated: 2025/06/12 15:29:03 by clai-ton         ###   ########.fr       */
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

size_t	mtime_diff(size_t start_utime, size_t end_utime)
{
	return ((end_utime - start_utime) / 1000);
}

/*
A more precise usleep() using gettimeofday(),
as usleep() only guarantees minimum sleep time.
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

void	wait_for_start_time(size_t start_utime)
{
	if (ft_get_utime() < start_utime)
		ft_usleep(start_utime - ft_get_utime());
}
