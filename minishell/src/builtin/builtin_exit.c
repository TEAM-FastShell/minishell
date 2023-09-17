/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seokklee <seokklee@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/07 19:46:04 by seokklee          #+#    #+#             */
/*   Updated: 2023/09/15 17:29:38 by seokklee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_num_str(char *n);

void	builtin_exit(t_node *node)
{
	int	i;

	if (node->pipe_type == W_PIPE || node->pipe_type == RW_PIPE)
		exit(g_exit_status);
	i = 0;
	while (node->cmd_args[i])
		i++;
	if (i == 1)
		printf("exit\n");
	else if (i == 2 && is_num_str(node->cmd_args[1]))
		g_exit_status = ft_atoi(node->cmd_args[1]);
	else if (i > 2 && is_num_str(node->cmd_args[1]))
	{
		error_str_code(node, TOO_MANY_ARG, 1);
		return ;
	}
	else
	{
		error_str_str_code(node, NUM_ARG_REQ, 255);
		return ;
	}
	if (node->pipe_type == NO_PIPE)
		exit(g_exit_status);
}

static int	is_num_str(char *n)
{
	int	i;

	i = 0;
	while (n[i])
	{
		if (!ft_isdigit(n[i]))
			return (0);
		i++;
	}
	return (1);
}
