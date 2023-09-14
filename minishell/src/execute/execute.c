/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seokklee <seokklee@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/07 19:46:21 by seokklee          #+#    #+#             */
/*   Updated: 2023/09/14 19:30:20 by seokklee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parse.h"

static void	wait_child(t_data *data);
static char	*get_cmd(t_data *data, char *cmd_uncertain);
static void	exec_child(t_data *data, t_node *node);

void	execute(t_data *data)
{
	t_node	*cur;

	cur = data->list->head;
	set_signal(execute_sigint_handler, execute_sigquit_handler);
	while (cur != NULL)
	{
		if (cur->cmd_args[0])
		{
			if (cur->redir_type != NO_REDIR)
			{
				g_exit_status = 0;
				exec_redir(data, cur);
				if (g_exit_status)
					break ;
				cur = cur->next;
				continue ;
			}
			else if (cur->pipe_type != NO_PIPE)
				ft_pipe(data, cur);
			exec_cmd(data, cur);
		}
		cur = cur->next;
	}
	free_pipe_fd(data);
	free_list(data->list);
}

void	exec_cmd(t_data *data, t_node *node)
{
	if (is_builtin(node->cmd_args) && node->pipe_type == NO_PIPE)
	{
		if (data->input_fd == STDIN_FILENO && data->output_fd == STDOUT_FILENO)
			return (exec_builtin(data, node));
	}
	ft_fork(node);
	if (node->pid == 0)
		exec_child(data, node);
	else if (node->pid > 0)
	{
		if (data->input_fd != STDIN_FILENO && data->input_fd > 0)
			ft_close(data->input_fd);
		if (data->output_fd != STDOUT_FILENO && data->output_fd > 0)
			ft_close(data->output_fd);
		data->input_fd = 0;
		data->output_fd = 1;
		if (node->pipe_type == NO_PIPE || node->pipe_type == R_PIPE)
		{
			close_all_pipes(data);
			wait_child(data);
		}
	}
}

static void	exec_child(t_data *data, t_node *node)
{
	char	*cmd;

	control_pipe(data, node);
	connect_fd(data);
	close_fd(data, node);
	if (node->redir_type != NO_REDIR)
		exit(g_exit_status);
	if (is_builtin(node->cmd_args))
	{
		exec_builtin(data, node);
		exit(g_exit_status);
	}
	cmd = get_cmd(data, node->cmd_args[0]);
	if (!cmd)
	{
		error_str_code(node, CMD_NOT_FOUND, 127);
		exit(127);
	}
	if (execve(cmd, node->cmd_args, data->envp) < 0)
	{
		error_str_code(node, strerror(errno), 127);
		exit(127);
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
	if (WIFSIGNALED(g_exit_status))
		g_exit_status = 128 + WTERMSIG(g_exit_status);
	if (WIFEXITED(g_exit_status))
		g_exit_status = WEXITSTATUS(g_exit_status);
}

static char	*get_cmd(t_data *data, char *cmd_uncertain)
{
	char	*tmp;
	char	*cmd;
	char	**path_tab;
	char	**address;

	if (!cmd_uncertain)
		return (NULL);
	else if (cmd_uncertain[0] == '/')
		return (cmd_uncertain);
	path_tab = ft_split(get_envv_data(data->envp, "PATH"), ':');
	address = path_tab;
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
	free_tab(address);
	return (NULL);
}
