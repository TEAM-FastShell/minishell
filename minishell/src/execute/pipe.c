/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seokklee <seokklee@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/07 19:46:23 by seokklee          #+#    #+#             */
/*   Updated: 2023/09/07 19:52:08 by seokklee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	cntl_pipe(t_data *data, t_node *node);
static void	close_pipe(t_data *data, t_node *node);
static void	change_fd(t_data *data, t_node *node, int fd);

void	connect_pipe(t_data *data, t_node *node)
{
	int	fd;

	if (node->idx == -1 || data->list->cmd_cnt < 1)
		return ;
	if (node->pipe_type == R_PIPE || node->pipe_type == RW_PIPE)
	{
		if (node->idx == 0 || node->prev->redir_type != NO_REDIR)
		{
			fd = open("/dev/null", O_RDONLY);
			data->input_fd = fd;
			ft_dup2(data->input_fd, STDIN_FILENO);
			ft_close(data->input_fd);
			return ;
		}
	}
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
		change_fd(data, node, 1);
	}
	else if (node->pipe_type == RW_PIPE)
	{
		change_fd(data, node, 0);
		change_fd(data, node, 1);
	}
	else if (node->pipe_type == R_PIPE)
	{
		ft_close(data->pipe_fd[node->idx - 1][1]);
		change_fd(data, node, 0);
	}
}

static void	change_fd(t_data *data, t_node *node, int fd)
{
	if (fd == 0)
	{
		if (data->input_fd == STDIN_FILENO)
			data->input_fd = data->pipe_fd[node->idx - 1][0];
		else
			ft_close(data->pipe_fd[node->idx - 1][0]);
	}
	else if (fd == 1)
	{
		if (data->output_fd == STDOUT_FILENO)
			data->output_fd = data->pipe_fd[node->idx][1];
		else
			ft_close(data->pipe_fd[node->idx][1]);
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
		ft_close(data->pipe_fd[node->idx][0]);
		ft_close(data->pipe_fd[node->idx][1]);
	}
}
