/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seokklee <seokklee@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/28 13:36:00 by seokklee          #+#    #+#             */
/*   Updated: 2023/08/29 17:06:50 by seokklee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void	cntl_pipe(t_data *data, t_node *node);
static void	close_pipe(t_data *data, t_node *node);

void	connect_pipe(t_data *data, t_node *node)
{
	cntl_pipe(data, node);
	if (data->input_fd != STDIN_FILENO)
		ft_dup2(data->input_fd, STDIN_FILENO);
	if (data->output_fd != STDOUT_FILENO)
		ft_dup2(data->output_fd, STDOUT_FILENO);
	close_pipe(data, node);
}

static void	cntl_pipe(t_data *data, t_node *node)
{
	if (node->pipe_type == NO_PIPE)
		return ;
	if (node->pipe_type == W_PIPE || node->pipe_type == RW_PIPE)
	{
		ft_close(data->pipe_fd[node->idx][0]);
		if (data->output_fd == STDOUT_FILENO)
			data->output_fd = data->pipe_fd[node->idx][1];
		else
			ft_close(data->pipe_fd[node->idx][1]);
	}
	if (node->pipe_type == R_PIPE || node->pipe_type == RW_PIPE)
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
	if (node->pipe_type == NO_PIPE)
		return ;
	if (node->pipe_type == W_PIPE || node->pipe_type == RW_PIPE)
	{
		ft_close(data->output_fd);
		if (data->input_fd != STDIN_FILENO)
			ft_close(data->input_fd);
	}
	if (node->pipe_type == R_PIPE || node->pipe_type == RW_PIPE)
	{
		ft_close(data->input_fd);
		if (data->output_fd != STDOUT_FILENO)
			ft_close(data->output_fd);
	}
}

