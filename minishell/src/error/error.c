/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seokklee <seokklee@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/07 19:46:18 by seokklee          #+#    #+#             */
/*   Updated: 2023/09/14 12:11:48 by seokklee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	error_code(int code)
{
	g_exit_status = code;
	ft_putendl_fd("exit", STDERR_FILENO);
}

void	error_str_code(t_node *node, char *str, int code)
{
	g_exit_status = code;
	ft_putstr_fd("fastshell: ", STDERR_FILENO);
	ft_putstr_fd(node->cmd_args[0], STDERR_FILENO);
	ft_putstr_fd(": ", STDERR_FILENO);
	ft_putendl_fd(str, STDERR_FILENO);
}

void	error_str_str_code(t_node *node, char *str, int code)
{
	g_exit_status = code;
	ft_putstr_fd("fastshell: ", STDERR_FILENO);
	ft_putstr_fd(node->cmd_args[0], STDERR_FILENO);
	ft_putstr_fd(": \'", STDERR_FILENO);
	if (node->cmd_args[2])
		ft_putstr_fd(node->cmd_args[2], STDERR_FILENO);
	else
		ft_putstr_fd(node->cmd_args[1], STDERR_FILENO);
	ft_putstr_fd("\': ", STDERR_FILENO);
	ft_putendl_fd(str, STDERR_FILENO);
}
