/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youyoon <youyoon@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/28 13:35:58 by seokklee          #+#    #+#             */
/*   Updated: 2023/09/01 13:02:57 by youyoon          ###   ########.fr       */
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
	int		i;

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
	/* free 정리 필요 */
	if (data->list->cmd_cnt > 1)
	{
		i = -1;
		while (data->pipe_fd[++i])
		{
			free(data->pipe_fd[i]);
			data->pipe_fd[i] = NULL;
		}
		free(data->pipe_fd);
		data->pipe_fd = NULL;
	}
	free_list(data->list);
}

static void	exec_pipe(t_data *data, t_node *node)
{
	if (node->redir_type != NO_REDIR)
	{
		exec_redir(data, node);
		return ;
	}
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
		if (node->idx == data->list->cmd_cnt - 1)
		{
			close_all_pipes(data);
			wait_child(data);
		}
	}
}

static void	wait_child(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->list->cmd_cnt)
	{
		ft_wait();
		i++;
	}
	waitpid(data->list->tail->pid, &g_exit_status, 0);
}

static void	exec_child(t_data *data, t_node *node)
{
	char	*cmd;

	connect_pipe(data, node);
	if (is_builtin(node->cmd_args))
		exec_builtin(data, node);
	cmd = get_cmd(ft_split(getenv("PATH"), ':'), node->cmd_args[0]);
	if (!cmd)
		error_str_code(node, CMD_NOT_FOUND, 127);
	if (execve(cmd, node->cmd_args, data->envp) < 0)
		ft_putendl_fd(strerror(errno), STDERR_FILENO);
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
