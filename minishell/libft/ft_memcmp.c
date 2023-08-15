/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youyoon <youyoon@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 18:50:07 by youyoon           #+#    #+#             */
/*   Updated: 2022/11/14 19:41:37 by youyoon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	char	*tmp_s1;
	char	*tmp_s2;

	tmp_s1 = (char *)s1;
	tmp_s2 = (char *)s2;
	while (n--)
	{
		if (*tmp_s1 > *tmp_s2)
			return ((unsigned char)*tmp_s1 - (unsigned char)*tmp_s2);
		else if (*tmp_s1 < *tmp_s2)
			return ((unsigned char)*tmp_s1 - (unsigned char)*tmp_s2);
		tmp_s1++;
		tmp_s2++;
	}
	return (0);
}
