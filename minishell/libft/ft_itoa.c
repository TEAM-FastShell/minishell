/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youyoon <youyoon@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/18 14:10:05 by youyoon           #+#    #+#             */
/*   Updated: 2022/11/18 15:46:19 by youyoon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	malloc_cnt(int num)
{
	unsigned int	cnt;

	cnt = 0;
	if (num < 0)
	{
		cnt++;
		num *= (-1);
	}
	else if (num == 0)
		return (1);
	while (num)
	{
		num /= 10;
		cnt++;
	}
	return (cnt);
}

static char	*exception(char *tmp, int n)
{
	if (n == 0)
	{
		return ((char *)ft_memcpy(tmp, "0", 2));
	}
	else if (n == -2147483648)
	{
		return ((char *)ft_memcpy(tmp, "-2147483648", 12));
	}
	return (0);
}

static char	*chrcpy(int num, char *tmp)
{
	char	*ret_addr;

	ret_addr = tmp;
	*ret_addr-- = 0;
	while (num)
	{
		*ret_addr-- = (num % 10) + '0';
		num /= 10;
	}
	return (ret_addr);
}

char	*ft_itoa(int n)
{
	unsigned int	count;
	char			*ret;
	int				check;

	check = 0;
	count = malloc_cnt(n) + 1;
	ret = (char *) malloc(sizeof(char) * count);
	if (!ret)
		return (0);
	if (n == 0 || n == -2147483648)
	{
		ret = exception(ret, n);
		return (ret);
	}
	else if (n < 0)
	{
		ret[0] = '-';
		n *= (-1);
		check = 1;
	}
	ret += count - 1;
	ret = chrcpy(n, ret);
	if (!check)
		return (++ret);
	return (ret);
}
