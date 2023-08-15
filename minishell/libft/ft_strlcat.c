/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youyoon <youyoon@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/11 16:02:11 by youyoon           #+#    #+#             */
/*   Updated: 2022/11/11 17:00:01 by youyoon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t len)
{
	size_t	dest_len;
	size_t	src_len;
	size_t	i;
	size_t	dest_len_tmp;

	i = 0;
	dest_len = ft_strlen(dst);
	dest_len_tmp = dest_len;
	src_len = ft_strlen(src);
	dst += dest_len_tmp;
	while (*src && ((dest_len + i + 1) < len))
	{
		*dst++ = *src++;
		i++;
	}
	*dst = 0;
	if (dest_len < len)
		return (dest_len + src_len);
	else
		return (src_len + len);
}
