#include "../../include/minishell.h"

static void	cntl_pipe(t_data *data, t_node *node);
static void	close_pipe(t_data *data, t_node *node);

void	connect_pipe(t_data *data, t_node *node)
{
	if (node->idx == -1 || data->list->cmd_cnt < 1)
		return ;
	cntl_pipe(data, node);
	if (data->input_fd != STDIN_FILENO)
		ft_dup2(data->input_fd, STDIN_FILENO);
	if (data->output_fd != STDOUT_FILENO)
		ft_dup2(data->output_fd, STDOUT_FILENO);
	close_pipe(data, node);
}

static void	cntl_pipe(t_data *data, t_node *node)
{
	if (node->pipe_type == W_PIPE)
	{
		ft_close(data->pipe_fd[node->idx][0]);
		if (data->output_fd == STDOUT_FILENO)
			data->output_fd = data->pipe_fd[node->idx][1];
		else
			ft_close(data->pipe_fd[node->idx][1]);
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
		ft_close(data->pipe_fd[node->idx - 1][1]);
		if (data->input_fd == STDIN_FILENO)
			data->input_fd = data->pipe_fd[node->idx - 1][0];
		else
			ft_close(data->pipe_fd[node->idx - 1][0]);
	}
}

static void	close_pipe(t_data *data, t_node *node)
{
	if (node->pipe_type == W_PIPE)
	{
		if (data->output_fd == data->pipe_fd[node->idx][1])
			ft_close(data->output_fd);
	}
	else if (node->pipe_type == RW_PIPE)
	{
		if (data->input_fd == data->pipe_fd[node->idx - 1][0])
			ft_close(data->input_fd);
		if (data->output_fd == data->pipe_fd[node->idx][1])
			ft_close(data->output_fd);
	}
	else if (node->pipe_type == R_PIPE)
	{
		if (data->input_fd == data->pipe_fd[node->idx - 1][0])
			ft_close(data->input_fd);
	}
}

