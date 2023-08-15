/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youyoon <youyoon@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/17 19:05:19 by youyoon           #+#    #+#             */
/*   Updated: 2022/11/17 19:15:45 by youyoon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*tmp;
	char	*ret;
	size_t	len;

	len = ft_strlen(s1) + ft_strlen(s2);
	tmp = (char *) malloc(sizeof(char) * (len + 1));
	ret = tmp;
	if (!tmp)
		return (0);
	while (*s1)
	{
		*tmp++ = *s1++;
	}
	while (*s2)
	{
		*tmp++ = *s2++;
	}
	*tmp = '\0';
	return (ret);
}
