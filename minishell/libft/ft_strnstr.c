/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youyoon <youyoon@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 16:23:54 by youyoon           #+#    #+#             */
/*   Updated: 2022/11/18 14:04:17 by youyoon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	search(const char *haystack, const char *needle, size_t *len)
{
	int		i;
	size_t	tmp;

	i = 0;
	tmp = *len;
	while (tmp-- && needle[i])
	{
		if (needle[i] == *haystack)
		{
			haystack++;
			i++;
		}
		else
			break ;
	}
	if (!needle[i])
		return (1);
	return (0);
}

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	char	*ret_addr;

	if (!(*needle))
		return ((char *) haystack);
	if (!len)
		return (0);
	while (len && *haystack)
	{
		if (*haystack == needle[0])
		{
			ret_addr = (char *)haystack;
			if (search(haystack, &needle[0], &len))
			{
				return (ret_addr);
			}
		}
		haystack++;
		len--;
	}
	return (0);
}
