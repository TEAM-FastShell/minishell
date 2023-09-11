/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seokklee <seokklee@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/07 19:46:23 by seokklee          #+#    #+#             */
/*   Updated: 2023/09/11 14:44:45 by seokklee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	check_only_redir(t_data *data, t_node *node);
static void	pipe_without_input(t_data *data, t_node *node);
static void	pipe_without_output(t_data *data, t_node *node);
static void	change_fd(t_data *data, t_node *node, int fd);

void	control_pipe(t_data *data, t_node *node)
{
	if (node->pipe_type == NO_PIPE)
		return ;
	if (check_only_redir(data, node))
		return ;
	if (node->pipe_type == W_PIPE)
		change_fd(data, node, 1);
	else if (node->pipe_type == RW_PIPE)
	{
		change_fd(data, node, 0);
		change_fd(data, node, 1);
	}
	else if (node->pipe_type == R_PIPE)
		change_fd(data, node, 0);
}

static int	check_only_redir(t_data *data, t_node *node)
{
	int	flag;

	flag = 0;
	if (node->pipe_type == W_PIPE || node->pipe_type == RW_PIPE)
	{
		if (node->next->redir_type != NO_REDIR \
		&& node->next->pipe_type != NO_PIPE)
		{
			pipe_without_output(data, node);
			flag = 1;
		}
	}
	if (node->pipe_type == RW_PIPE || node->pipe_type == R_PIPE)
	{
		if (node->prev->redir_type != NO_REDIR \
		&& node->prev->pipe_type != NO_PIPE)
		{
			pipe_without_input(data, node);
			flag = 1;
		}
	}
	return (flag);
}

static void	pipe_without_input(t_data *data, t_node *node)
{
	int	fd;

	if (data->input_fd == STDIN_FILENO)
	{
		fd = open("/dev/null", O_RDONLY);
		data->input_fd = fd;
	}
	else
		data->input_fd = STDIN_FILENO;
	if (node->pipe_type == RW_PIPE && \
	(data->output_fd == STDOUT_FILENO || data->output_fd == -1))
		change_fd(data, node, 1);
}

static void	pipe_without_output(t_data *data, t_node *node)
{
	int	fd;

	if (data->output_fd == STDOUT_FILENO)
	{
		fd = open("/dev/null", O_WRONLY);
		data->output_fd = fd;
	}
	else
		data->output_fd = STDOUT_FILENO;
	if (node->pipe_type == RW_PIPE && \
	(data->input_fd == STDIN_FILENO || data->input_fd == -1))
		change_fd(data, node, 0);
}

static void	change_fd(t_data *data, t_node *node, int fd)
{
	if (fd == 0)
	{
		if (data->input_fd == STDIN_FILENO)
			data->input_fd = data->pipe_fd[node->idx - 1][0];
	}
	else if (fd == 1)
	{
		if (data->output_fd == STDOUT_FILENO)
			data->output_fd = data->pipe_fd[node->idx][1];
	}
}
