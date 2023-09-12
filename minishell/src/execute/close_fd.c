/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   close_fd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seokklee <seokklee@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/10 14:58:29 by seokklee          #+#    #+#             */
/*   Updated: 2023/09/11 17:44:27 by seokklee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	close_pipe(t_data *data, t_node *node);
static void	ft_close_pipe_fd(t_data *data, int idx);

void	close_fd(t_data *data, t_node *node)
{
	if (node->redir_type != NO_REDIR)
		return ;
	if (node->pipe_type != NO_PIPE)
		close_pipe(data, node);
	data->input_fd = STDIN_FILENO;
	data->output_fd = STDOUT_FILENO;
}

static void	close_pipe(t_data *data, t_node *node)
{
	if (node->idx == 0)
	{
		ft_close(data->pipe_fd[node->idx][0]);
	}
	else if (node->idx == data->list->cmd_cnt - 1)
	{
		ft_close(data->pipe_fd[node->idx - 1][1]);
		ft_close(data->pipe_fd[node->idx][0]);
		ft_close(data->pipe_fd[node->idx][1]);
	}
	else
	{
		ft_close(data->pipe_fd[node->idx - 1][1]);
		ft_close(data->pipe_fd[node->idx][0]);
	}
	ft_close_pipe_fd(data, node->idx - 1);
}

static void	ft_close_pipe_fd(t_data *data, int idx)
{
	int	i;

	if (idx < 1)
		return ;
	i = 0;
	while (i < idx)
	{
		ft_close(data->pipe_fd[i][0]);
		ft_close(data->pipe_fd[i][1]);
		i++;
	}
}
