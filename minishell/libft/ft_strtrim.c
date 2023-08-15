/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youyoon <youyoon@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/17 19:16:43 by youyoon           #+#    #+#             */
/*   Updated: 2022/11/18 14:04:38 by youyoon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*find_start(char *ptr, char *set)
{
	while (*ptr)
	{
		if (!ft_strchr(set, *ptr))
			break ;
		ptr++;
	}
	return (ptr);
}

static char	*find_end(char *ptr, char *set)
{
	while (*ptr)
	{
		if (!ft_strchr(set, *ptr))
			break ;
		ptr--;
	}
	return (ptr);
}

static char	*my_malloc(void)
{
	char	*ret;

	ret = (char *) malloc(sizeof(char));
	if (!ret)
		return (0);
	ret[0] = 0;
	return (ret);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*start;
	char	*end;
	char	*tmp;
	char	*ret;

	if (!ft_strlen(s1))
		return (my_malloc());
	start = find_start((char *)s1, (char *)set);
	end = find_end((char *)s1 + (ft_strlen(s1) - 1), (char *)set);
	if (end < start)
	{
		return (my_malloc());
	}
	tmp = (char *) malloc(sizeof(char) * (end - start + 2));
	ret = tmp;
	if (!tmp)
		return (0);
	while (start <= end)
	{
		*tmp++ = *start++;
	}
	*tmp = 0;
	return (ret);
}
