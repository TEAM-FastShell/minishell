/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_parse.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youyoon <youyoon@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/16 15:52:10 by youyoon           #+#    #+#             */
/*   Updated: 2023/08/26 19:29:30 by youyoon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"
#include "../../../include/parse.h"

t_double_list	*init_list(void)
{
	t_double_list	*ret;

	ret = (t_double_list *) malloc(sizeof(t_double_list));
	if (!ret)
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

static char	**copy_evnp(char **envp)
{
	int		i;
	char	**ret;

	i = 0;
	while (envp[i])
		i++;
	ret = (char **) malloc(sizeof(char *) * (i + 1));
	i = -1;
	while (envp[++i])
		ret[i] = ft_strdup(envp[i]);
	ret[i] = NULL;
	return (ret);
}

t_data	*init_data(char **envp, t_double_list *list)
{
	t_data	*ret;
	int		i;

	ret = (t_data *) malloc(sizeof(t_data));
	if (!ret)
		return (NULL);
	ret->envp = copy_evnp(envp);
	if (!ret->envp)
		return (NULL);
	ret->list = list;
	i = -1;
	while (list->cmd_cnt > 1 && (++i < 2))
	{
		ret->pipe_fd[i] = (int *) malloc(sizeof(int) * (list->cmd_cnt - 1));
		if (!ret->pipe_fd[i])
			return (NULL);
	}
	ret->input_fd = 0;
	ret->output_fd = 1;
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
