/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youyoon <youyoon@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/17 16:42:15 by youyoon           #+#    #+#             */
/*   Updated: 2022/11/18 14:04:48 by youyoon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	str_cpy(char *dest, char *src, size_t len)
{
	while (*src && --len)
	{
		*dest = *src;
		src++;
		dest++;
	}
	*dest = 0;
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char			*tmp;

	if (start >= ft_strlen(s))
	{
		tmp = (char *) malloc(sizeof(char));
		if (!tmp)
			return (0);
		tmp[0] = '\0';
		return (tmp);
	}
	if (start + len > ft_strlen(s))
	{
		tmp = (char *) malloc(sizeof(char) * (ft_strlen(s) - start + 1));
		if (!tmp)
			return (0);
		str_cpy(tmp, (char *)s + start, ft_strlen(s) - start + 1);
	}
	else
	{
		tmp = (char *) malloc(sizeof(char) * (len + 1));
		if (!tmp)
			return (0);
		str_cpy(tmp, (char *)s + start, len + 1);
	}
	return (tmp);
}
