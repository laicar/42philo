/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_arg.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clai-ton <clai-ton@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 16:41:18 by clai-ton          #+#    #+#             */
/*   Updated: 2025/06/04 17:58:20 by clai-ton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static int	ft_strncmp(const char *s1, const char *s2, size_t length)
{
	size_t	i;

	if (length == 0 || !s1 || !s2)
		return (0);
	i = 0;
	while ((s1[i] || s2[i]) && i < length)
	{
		if (s1[i] != s2[i])
			return ((unsigned char) s1[i] - (unsigned char) s2[i]);
		i++;
	}
	return (0);
}

static int	validate_len(char *str, int *i)
{
	int	len;

	len = 0;
	while (str[len])
		++len;
	*i = 0;
	while (str[*i] == ' ' || str[*i] == '\n' || str[*i] == '\r'
		|| str[*i] == '\t' || str[*i] == '\v' || str[*i] == '\f')
		++(*i);
	len -= *i;
	if (len >= 12
		|| (len == 11
			&& ((str[*i] != '-' && str[*i] != '+')
				|| (str[*i] == '+' && ft_strncmp(str + *i, "+2147483647", 11) > 0)
				|| (str[*i] == '-' && ft_strncmp(str + *i, "-2147483648", 11) > 0)))
		|| (len == 10 && ft_strncmp(str + *i, "2147483647", 10) > 0))
		return (-1);
	return (len);
}

/*
Similar process and result to atoi(), except negative numbers and non-digit
characters in the string will return a -1 value, signifying an error.
The range for all of the program's arguments is supposed to fit into int.
*/
int	ft_parse_arg(char *str)
{
	int	n;
	int	i;

	n = 0;
	i = 0;
	if (validate_len(str, &i) == -1)
		return (-1);
	if (str[i] == '+')
		++i;
	else if (str[i] == '-')
		return (-1);
	while ('0' <= str[i] && str[i] <= '9')
	{
		n *= 10;
		n += (str[i] - '0');
		++i;
	}
	if (str[i])
		return (-1);
	return (n);
}
