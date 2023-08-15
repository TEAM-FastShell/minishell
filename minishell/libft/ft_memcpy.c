/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youyoon <youyoon@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 20:30:05 by youyoon           #+#    #+#             */
/*   Updated: 2022/11/11 16:53:28 by youyoon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	char		*tmp_dst;
	const char	*tmp_src;

	if (!dst && !src)
		return (0);
	tmp_src = src;
	tmp_dst = dst;
	while (n--)
	{
		*tmp_dst++ = *tmp_src++;
	}
	tmp_dst = 0;
	return (dst);
}
