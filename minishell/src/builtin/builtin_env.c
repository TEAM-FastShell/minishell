/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seokklee <seokklee@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/28 13:35:35 by seokklee          #+#    #+#             */
/*   Updated: 2023/08/28 13:35:36 by seokklee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	builtin_env(t_data *data, t_node *node)
{
	int	i;

	i = 0;
	while (data->envp)
	{
		ft_putendl_fd(data->envp[i], data->output_fd);
		i++;
	}
	g_exit_status = 0;
}
