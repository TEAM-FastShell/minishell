/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seokklee <seokklee@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/07 19:46:13 by seokklee          #+#    #+#             */
/*   Updated: 2023/09/12 16:20:51 by seokklee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_builtin(char **cmd_args);

void	exec_builtin(t_data *data, t_node *node)
{
	char	*cmd;

	cmd = node->cmd_args[0];
	if (!ft_strncmp(cmd, "echo", ft_strlen("echo")))
		builtin_echo(node);
	else if (!ft_strncmp(cmd, "cd", ft_strlen("cd")))
		builtin_cd(data, node);
	else if (!ft_strncmp(cmd, "pwd", ft_strlen("pwd")))
		builtin_pwd();
	else if (!ft_strncmp(cmd, "export", ft_strlen("export")))
		builtin_export(data, node);
	else if (!ft_strncmp(cmd, "unset", ft_strlen("unset")))
		builtin_unset(data, node);
	else if (!ft_strncmp(cmd, "env", ft_strlen("env")))
		builtin_env(data);
	else if (!ft_strncmp(cmd, "exit", ft_strlen("exit")))
		builtin_exit(node);
	else if (!ft_strncmp(cmd, "history", ft_strlen("history")))
		builtin_history();
}

int	is_builtin(char **cmd_args)
{
	char	*cmd;
	size_t	cmd_len;

	cmd = cmd_args[0];
	cmd_len = ft_strlen(cmd);
	if ((!ft_strncmp(cmd, "echo", 4) && (cmd_len == ft_strlen("echo"))) || \
	(!ft_strncmp(cmd, "cd", 2) && (cmd_len == ft_strlen("cd"))) || \
	(!ft_strncmp(cmd, "pwd", 3) && (cmd_len == ft_strlen("pwd"))) || \
	(!ft_strncmp(cmd, "export", 6) && (cmd_len == ft_strlen("export"))) || \
	(!ft_strncmp(cmd, "unset", 5) && (cmd_len == ft_strlen("usnet"))) || \
	(!ft_strncmp(cmd, "env", 3) && (cmd_len == ft_strlen("env"))) || \
	(!ft_strncmp(cmd, "exit", 4) && (cmd_len == ft_strlen("exit"))) || \
	(!ft_strncmp(cmd, "history", 7) && (cmd_len == ft_strlen("history"))))
		return (1);
	return (0);
}
