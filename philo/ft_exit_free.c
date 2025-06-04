/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit_free.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clai-ton <clai-ton@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 16:44:11 by clai-ton          #+#    #+#             */
/*   Updated: 2025/01/17 12:23:43 by clai-ton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

//todo
void	ft_free_data(void/*t_sl *data*/)
{

}

void	ft_exit_free_data(/*t_sl *data, */char *message)
{
	//ft_free_data(data);
	ft_exit_error(message);
}

void	ft_exit_error(char *message)
{
	ft_putendl_fd(message, STDERR_FILENO);
	exit(EXIT_FAILURE);
}