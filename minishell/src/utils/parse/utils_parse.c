/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_parse.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youyoon <youyoon@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/16 15:52:10 by youyoon           #+#    #+#             */
/*   Updated: 2023/08/24 14:46:33 by youyoon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"
#include "../../../include/parse.h"

t_double_list	*init_list(void)
{
	t_double_list	*ret;

	if (!(ret = (t_double_list *) malloc(sizeof(t_double_list))))
		return (NULL);
	ret->head = NULL;
	ret->tail = NULL;
	ret->cnt = 0;
	ret->cmd_cnt = 0;
	return (ret);
}

/*
	cmt : token개수 + 1
	buff : input의 길이 + 1
	나머지 모두 0으로 초기화
*/
t_parse	*init_parse(int token_cnt, int input_len)
{
	t_parse	*ret;

	ret = (t_parse *) malloc(sizeof(t_parse));
	if (!(ret))
		return (NULL);
	ret->cmd = (char **) ft_calloc(token_cnt + 1, sizeof(char *));
	if (!(ret->cmd))
		return (NULL);
	ret->buff = (char *) ft_calloc(input_len + 1, sizeof(char));
	if (!(ret->buff))
		return (NULL);
	ret->quote = 0;
	ret->c_idx = 0;
	ret->b_idx = 0;
	ret->pipe_type = NO_PIPE;
	ret->redir_type = NO_REDIR;
	return (ret);
}

int	check_redir(char input, char input_next)
{
	if (input == '<')
	{
		if (input_next == '<')
			return (H_REDIR);
		else
			return (R_REDIR);
	}
	else if (input == '>')
	{
		if (input_next == '>')
			return (A_REDIR);
		else
			return (W_REDIR);
	}
	return (NO_REDIR);
}

void	set_pipe_type(t_double_list *list)
{
	t_node	*cur;

	cur = list->head;
	while (cur->pipe_type == 0)
		cur = cur->next;
	if (cur->pipe_type == RW_PIPE)
		cur->pipe_type = W_PIPE;
	cur = list->tail;
	while (cur->pipe_type == 0)
		cur = cur->prev;
	if (cur->pipe_type == RW_PIPE)
		cur->pipe_type = R_PIPE;
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
