/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youyoon <youyoon@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/11 11:46:47 by youyoon           #+#    #+#             */
/*   Updated: 2022/11/11 16:45:26 by youyoon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	char		*tmp_dst;
	const char	*tmp_src;

	if (!dst && !src)
		return (0);
	tmp_dst = dst;
	tmp_src = src;
	if (src > dst)
	{
		while (len--)
		{
			*tmp_dst++ = *tmp_src++;
		}
	}
	else
	{	
		tmp_dst += len;
		tmp_src += len;
		while (len--)
		{
			*--tmp_dst = *--tmp_src;
		}
	}
	return (dst);
}
