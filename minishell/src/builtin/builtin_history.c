/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_history.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seokklee <seokklee@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/08 14:21:26 by seokklee          #+#    #+#             */
/*   Updated: 2023/09/08 14:21:27 by seokklee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	builtin_history(void)
{
	HIST_ENTRY	**h_list;
	int			i;

	i = 0;
	h_list = history_list();
	if (h_list)
	{
		while (h_list[i])
		{
			printf("%d: %s\n", i + 1, h_list[i]->line);
			i++;
		}
	}
}
