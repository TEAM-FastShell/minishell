/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youyoon <youyoon@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/17 19:37:30 by youyoon           #+#    #+#             */
/*   Updated: 2022/11/18 14:08:54 by youyoon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	get_count_words(const char *s, const char c)
{
	size_t	count;

	count = 0;
	while (*s)
	{
		if (*s != c)
		{
			count++;
			while (*s && *s != c)
				s++;
		}
		else
			s++;
	}
	return (count);
}

static char	*get_next_addr(const char *s, const char c)
{
	while (*s && *s != c)
		s++;
	return ((char *)s);
}

static char	**free_elem(char **splited, size_t size)
{
	while (size--)
	{
		free(splited[size]);
		splited[size] = 0;
	}
	free(splited);
	splited = 0;
	return (0);
}

char	**ft_split(char const *s, char c)
{
	size_t	i;
	char	**result;
	char	*p;

	if (!s)
		return (0);
	result = (char **)malloc(sizeof(char *) * (get_count_words(s, c) + 1));
	if (!result)
		return (0);
	i = 0;
	while (*s)
	{
		if (*s != c)
		{
			p = get_next_addr(s, c);
			result[i] = (char *)malloc(p - s + 1);
			if (!result[i])
				return (free_elem(result, i));
			ft_strlcpy(result[i++], s, p - s + 1);
			s = p - 1;
		}
		s++;
	}
	result[i] = 0;
	return (result);
}
