#include "minishell.h"

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
				break ;
			}
			if (is_builtin(cur->cmd_args) && cur->pipe_type == NO_PIPE)
				exec_builtin(cur->cmd_args);
			else
				exec_pipe(data, cur);
		}
		cur = cur->next;
	}
	/* list clear */
}

void	exec_pipe(t_data *data, t_node *node)
{
	if (node->redir_type != NO_REDIR)
	{
		exec_redir(data, node);
		return ;
	}
	if (node->pipe_type != NO_PIPE)
		ft_pipe(data, node);
	ft_fork(node);
	if (node->pid == 0)
		exec_cmd(data, node);
	else if (node->pid > 0)
	{
		/*리다 복구 혹은 포크 하고 리다*/
		if (data->input_fd != 0)
			ft_close(data->input_fd);
		if (data->output_fd != 1)
			ft_close(data->output_fd);
		data->input_fd = 0;
		data->output_fd = 1;
		if (node->pipe_type == W_PIPE || NO_PIPE)
		{
			close_pipes(data);
			wait_child(data);
		}
	}
}

void	wait_child(t_data *data)
{
	int	i;

	i = 0;
	while (i++ < data->list->cnt)
		ft_wait();
	waitpid(data->list->tail->prev->pid, &data->status, 0);
}

void	exec_cmd(t_data *data, t_node *node)
{
	char	*cmd;

	connect_pipe(data, node);
	cmd = get_cmd(data->path_tab, node->cmd_args[0]);
	if (!cmd)
		/*error cmd not found*/
	if (execve(cmd, node->cmd_args, data->envp) < 0)
		/*error execve*/
}

void	connect_pipe(t_data *data, t_node *node)
{
	cntl_pipe(data, node);
	dup2(data->input_fd, STDIN_FILENO);
	dup2(data->output_fd, STDOUT_FILENO);
}

void	cntl_pipe(t_data *data, t_node *node)
{
	if (node->pipe_type == NO_PIPE)
		return ;
	else if (node->pipe_type == W_PIPE)
	{
		if (data->output_fd == STDOUT_FILENO)
			data->output_fd = data->pipe_fd[node->idx][1];
		if (data->input_fd != STDIN_FILENO)
			ft_close(STDIN_FILENO);
	}
	else if (node->pipe_type == RW_PIPE)
	{
		if (data->input_fd == STDIN_FILENO)
			data->input_fd = data->pipe_fd[node->idx - 1][0];
		else
			ft_close(data->pipe_fd[node->idx - 1][0]);
		if (data->output_fd == STDOUT_FILENO)
			data->output_fd = data->pipe_fd[node->idx][1];
		else
			ft_close(data->pipe_fd[node->idx][1]);
	}
	else if (node->pipe_type == R_PIPE)
	{
		if (data->input_fd == STDIN_FILENO)
			data->input_fd = data->pipe_fd[node->idx - 1][0];
		else
			ft_close(data->pipe_fd[node->idx - 1][0]);
	}
}

char	*get_cmd(char **path_tab, char *cmd_uncertain)
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
