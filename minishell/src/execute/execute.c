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
	/* list clear  free */
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
		exec_child(data, node);
	else if (node->pid > 0)
	{
		if (data->input_fd != STDIN_FILENO)
			ft_close(data->input_fd);
		if (data->output_fd != STDOUT_FILENO)
			ft_close(data->output_fd);
		data->input_fd = 0;
		data->output_fd = 1;
		if (node->pipe_type == W_PIPE || NO_PIPE)
		{
			close_all_pipes(data);
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

void	exec_child(t_data *data, t_node *node)
{
	char	*cmd;

	connect_pipe(data, node);
	cmd = get_cmd(data->path_tab, node->cmd_args[0]);
	if (!cmd)
		/*error cmd not found*/
	if (execve(cmd, node->cmd_args, data->envp) < 0)
		/*error execve*/
}
