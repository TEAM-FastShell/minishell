/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youyoon <youyoon@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/15 20:30:14 by youyoon           #+#    #+#             */
/*   Updated: 2023/09/03 16:05:00 by youyoon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include "../../include/parse.h"

int	is_whitespace(char *str)
{
	int	i;
	int	space;

	i = 0;
	space = 0;
	if ((int) ft_strlen(str) == 0)
		return (1);
	while (str[i])
	{
		if (str[i] == '\r' || str[i] == '\v' || \
				str[i] == '\t' || str[i] == '\f')
			return (1);
		else if (str[i] == ' ')
			space++;
		i++;
	}
	if ((int) ft_strlen(str) == space)
		return (1);
	return (0);
}

char	*ft_strtok(char *str, const char delim)
{
	static char		*stock = NULL;
	char			*ptr;
	int				flg;

	flg = 0;
	ptr = NULL;
	if (str != NULL)
		stock = ft_strdup(str);
	while (*stock != '\0')
	{
		if (flg == 0 && *stock != delim)
		{
			flg = 1;
			ptr = stock;
		}
		else if (flg == 1 && *stock == delim)
		{
			*stock = '\0';
			stock += 1;
			break ;
		}
		stock += 1;
	}
	return (ptr);
}
