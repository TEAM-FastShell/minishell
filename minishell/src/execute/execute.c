/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seokklee <seokklee@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/28 13:35:58 by seokklee          #+#    #+#             */
/*   Updated: 2023/09/04 15:12:25 by seokklee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include "../../include/parse.h"

static void	exec_pipe(t_data *data, t_node *node);
static void	wait_child(t_data *data);
static void	exec_child(t_data *data, t_node *node);
static char	*get_cmd(char **path_tab, char *cmd_uncertain);

void	execute(t_data *data)
{
	t_node	*cur;

	cur = data->list->head;
	while (cur != NULL)
	{
		if (cur->cmd_args[0])
		{
			if (cur->redir_type != NO_REDIR && cur->pipe_type == NO_PIPE)
			{
				exec_redir(data, cur);
				cur = cur->next;
				continue ;
			}
			if (is_builtin(cur->cmd_args) && cur->pipe_type == NO_PIPE)
				exec_builtin(data, cur);
			else
				exec_pipe(data, cur);
		}
		cur = cur->next;
	}
	free_pipe_fd(data);
	free_list(data->list);
}

static void	exec_pipe(t_data *data, t_node *node)
{
	if (node->redir_type != NO_REDIR)
		return (exec_redir(data, node));
	if (node->pipe_type != NO_PIPE && node->pipe_type != R_PIPE)
		ft_pipe(data, node);
	ft_fork(node);
	if (node->pid == 0)
		exec_child(data, node);
	else if (node->pid > 0)
	{
		if (data->input_fd != STDIN_FILENO)
			ft_close(data->input_fd);
		if (data->output_fd != STDOUT_FILENO)
			ft_close(data->output_fd);
		data->input_fd = 0;
		data->output_fd = 1;
		if (node->pipe_type == NO_PIPE)
			waitpid(node->pid, &g_exit_status, 0);
		else if(node->pipe_type == R_PIPE)
		{
			close_all_pipes(data);
			wait_child(data);
		}
	}
}

static void	wait_child(t_data *data)
{
	t_node	*cur;

	cur = data->list->head;
	while (cur->next != NULL)
	{
		waitpid(cur->pid, &g_exit_status, 0);
		cur = cur->next;
	}
	waitpid(data->list->tail->pid, &g_exit_status, 0);
}

static void	exec_child(t_data *data, t_node *node)
{
	char	*cmd;

	if (is_builtin(node->cmd_args))
	{
		exec_builtin(data, node);
		return ;
	}
	connect_pipe(data, node);
	cmd = get_cmd(ft_split(get_envv_data(data->envp, "PATH"), ':'), node->cmd_args[0]);
	if (!cmd)
	{
		error_str_code(node, CMD_NOT_FOUND, 127);
		exit(g_exit_status);
	}
	if (execve(cmd, node->cmd_args, data->envp) < 0)
		ft_putendl_fd(strerror(errno), STDERR_FILENO);
	exit(g_exit_status);
}

static char	*get_cmd(char **path_tab, char *cmd_uncertain)
{
	char	*tmp;
	char	*cmd;

	if (!cmd_uncertain)
		return (NULL);
	while (*path_tab)
	{
		tmp = ft_strjoin(*path_tab, "/");
		cmd = ft_strjoin(tmp, cmd_uncertain);
		free(tmp);
		if (access(cmd, X_OK) == 0)
			return (cmd);
		free(cmd);
		path_tab++;
	}
	return (NULL);
}
