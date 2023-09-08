/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_clear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seokklee <seokklee@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/07 19:47:09 by seokklee          #+#    #+#             */
/*   Updated: 2023/09/08 17:15:38 by seokklee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	double_list_clear(t_double_list *list)
{
	t_node	*cur;
	t_node	*tmp;

	cur = list->head;
	while (cur)
	{
		tmp = cur->next;
		cur->prev = NULL;
		cur->next = NULL;
		free_tab(cur->cmd_args);
		cur->pipe_type = 0;
		cur->redir_type = 0;
		cur->pid = 0;
		cur->idx = 0;
		free(cur);
		cur = tmp;
	}
	free(list);
	list = NULL;
}

void	free_tab(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
	{
		free(tab[i]);
		tab[i] = NULL;
		i++;
	}
	free(tab);
	tab = NULL;
}

void	close_all_pipes(t_data *data)
{
	int	i;

	if (data->list->cmd_cnt <= 1)
		return ;
	i = 0;
	while (i < data->list->cmd_cnt)
	{
		ft_close(data->pipe_fd[i][0]);
		ft_close(data->pipe_fd[i][1]);
		i++;
	}
}

void	pipe_with_redir(t_data *data, t_node *node)
{
	int	fd;

	fd = open("/dev/null", O_RDONLY);
	data->input_fd = fd;
	ft_dup2(data->input_fd, STDIN_FILENO);
	ft_close(data->input_fd);
	if (node->pipe_type == RW_PIPE)
	{
		data->output_fd = data->pipe_fd[node->idx][1];
		ft_dup2(data->output_fd, STDOUT_FILENO);
		ft_close(data->output_fd);
	}
	return ;
}
