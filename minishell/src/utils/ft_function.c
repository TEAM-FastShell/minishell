/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_function.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seokklee <seokklee@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/07 19:47:02 by seokklee          #+#    #+#             */
/*   Updated: 2023/09/07 19:47:03 by seokklee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_pipe(t_data *data, t_node *node)
{
	if (node->idx == -1 || data->list->cmd_cnt < 1)
		return ;
	if (pipe(data->pipe_fd[node->idx]) < 0)
		ft_putendl_fd(strerror(errno), STDERR_FILENO);
}

void	ft_fork(t_node *node)
{
	node->pid = fork();
	if (node->pid < 0)
		ft_putendl_fd(strerror(errno), STDERR_FILENO);
}

void	ft_dup2(int new_fd, int origin_fd)
{
	if (dup2(new_fd, origin_fd) < 0)
	{
		printf("dup2 error\n");
		ft_putendl_fd(strerror(errno), STDERR_FILENO);
	}
}

void	ft_close(int fd)
{
	if (close(fd) < 0)
	{
		printf("close error\n");
		ft_putendl_fd(strerror(errno), STDERR_FILENO);
	}
}

void	ft_wait(void)
{
	if (wait(NULL) < 0)
		ft_putendl_fd(strerror(errno), STDERR_FILENO);
}
