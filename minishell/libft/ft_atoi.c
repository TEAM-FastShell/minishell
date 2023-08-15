/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youyoon <youyoon@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/11 17:43:35 by youyoon           #+#    #+#             */
/*   Updated: 2022/11/18 13:57:35 by youyoon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	check_isspace(char c)
{
	if (c == ' ' || c == '\n' || c == '\t')
		return (1);
	else if (c == '\v' || c == '\f' || c == '\r')
		return (1);
	return (0);
}

int	ft_atoi(const char *str)
{
	int	num;
	int	minus_count;
	int	sign;

	sign = 0;
	minus_count = 0;
	num = 0;
	while (check_isspace(*str))
		str++;
	while (*str == '-' || *str == '+')
	{
		if (*str == '-')
			minus_count++;
		str++;
		sign++;
	}
	while (*str >= '0' && *str <= '9')
	{
		num = num * 10 + *str++ - '0';
	}
	if (minus_count == 1)
		num = -num;
	if (sign > 1)
		num = 0;
	return (num);
}
