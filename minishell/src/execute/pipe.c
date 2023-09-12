/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seokklee <seokklee@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/07 19:46:23 by seokklee          #+#    #+#             */
/*   Updated: 2023/09/12 13:00:37 by seokklee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	check_next_node(t_data *data, t_node *node);
static int	check_prev_node(t_data *data, t_node *node);
static void	change_fd(t_data *data, t_node *node, int fd);

void	control_pipe(t_data *data, t_node *node)
{
	if (node->pipe_type == NO_PIPE || node->redir_type != NO_REDIR)
		return ;
	if (check_next_node(data, node) || check_prev_node(data, node))
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

static int	check_next_node(t_data *data, t_node *node)
{
	if (node->next && node->next->redir_type != NO_REDIR \
	&& node->next->pipe_type != NO_PIPE)
	{
		if (node->idx < data->list->cmd_cnt - 1)
			ft_close(data->pipe_fd[node->idx][1]);
		if (data->output_fd == STDOUT_FILENO)
			data->output_fd = open("/dev/null", O_WRONLY);
		if (node->idx > 0 && data->input_fd == STDIN_FILENO)
			change_fd(data, node, 0);
		return (1);
	}
	return (0);
}

static int	check_prev_node(t_data *data, t_node *node)
{
	if (node->prev && node->prev->redir_type != NO_REDIR \
	&& node->prev->pipe_type != NO_PIPE)
	{
		if (node->idx > 0)
			ft_close(data->pipe_fd[node->idx - 1][0]);
		if (data->input_fd == STDIN_FILENO)
			data->input_fd = open("/dev/null", O_RDONLY);
		if (node->idx < data->list->cmd_cnt - 1 \
		&& data->output_fd == STDOUT_FILENO)
			change_fd(data, node, 1);
		return (1);
	}
	return (0);
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
