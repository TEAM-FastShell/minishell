/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_parse_list2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youyoon <youyoon@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/26 16:41:40 by youyoon           #+#    #+#             */
/*   Updated: 2023/08/26 16:51:01 by youyoon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"
#include "../../../include/parse.h"

static int	count_pipe_type(t_double_list *list)
{
	int		cnt;
	t_node	*cur;

	cnt = 0;
	cur = list->head;
	while (cur)
	{
		if (cur->pipe_type > 0)
			cnt++;
		cur = cur->next;
	}
	return (cnt);
}

void	set_pipe_type(t_double_list *list)
{
	t_node	*cur;
	int		pipe_cnt;

	pipe_cnt = count_pipe_type(list);
	if (pipe_cnt > 0)
	{
		cur = list->head;
		while (cur->pipe_type == 0)
			cur = cur->next;
		if (cur->pipe_type == RW_PIPE)
			cur->pipe_type = W_PIPE;
		list->tail->pipe_type = R_PIPE;
	}
}

void	set_list_idx(t_double_list *list)
{
	t_node	*cur;
	int		i;

	i = 0;
	cur = list->head;
	while (cur)
	{
		cur->idx = i;
		i++;
		cur = cur->next;
	}
}
