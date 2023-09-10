/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youyoon <youyoon@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/17 01:08:33 by youyoon           #+#    #+#             */
/*   Updated: 2023/09/10 14:16:40 by youyoon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s)
{
	char	*tmp;

	tmp = (char *) malloc(sizeof(char) * (ft_strlen(s) + 1));
	if (!tmp)
	{
		return (0);
	}
	ft_strlcpy(tmp, s, ft_strlen(s) + 1);
	return (tmp);
}
