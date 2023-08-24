/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youyoon <youyoon@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/15 20:30:14 by youyoon           #+#    #+#             */
/*   Updated: 2023/08/24 13:39:46 by youyoon          ###   ########.fr       */
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
