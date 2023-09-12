/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_parse.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seokklee <seokklee@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/07 19:47:18 by seokklee          #+#    #+#             */
/*   Updated: 2023/09/12 16:54:30 by seokklee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parse.h"

void	init_list(t_double_list *list)
{
	list->head = NULL;
	list->tail = NULL;
	list->cnt = 0;
	list->cmd_cnt = 0;
}

char	**copy_env(char **env)
{
	char	**ret;
	int		i;

	i = 0;
	while (env[i])
		i++;
	ret = (char **) malloc(sizeof(char *) * (i + 1));
	if (!ret)
		return (NULL);
	i = 0;
	while (env[i])
	{
		ret[i] = ft_strdup(env[i]);
		i++;
	}
	ret[i] = NULL;
	return (ret);
}

void	init_parse(t_parse *parse, int token_cnt, t_data *data, int input_len)
{
	parse->cmd = (char **) ft_calloc(token_cnt + 1, sizeof(char *));
	parse->token_cnt = token_cnt;
	if (!parse->cmd)
		return (parse_error(NULL, NULL, NULL, MALLOC_ERROR));
	parse->buff = (char *) ft_calloc(input_len + 1, sizeof(char));
	if (!parse->buff)
		return (parse_error(NULL, parse, NULL, MALLOC_ERROR));
	parse->env = copy_env(data->envp);
	if (!parse->env)
		return (parse_error(NULL, parse, NULL, MALLOC_ERROR));
	parse->quote = 0;
	parse->c_idx = 0;
	parse->b_idx = 0;
	parse->pipe_type = NO_PIPE;
	parse->redir_type = NO_REDIR;
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

void	init_in_while_data(t_data *data, t_double_list *list)
{
	int	i;

	if (!list->head)
		return ;
	if (list->cmd_cnt >= 1)
	{
		data->pipe_fd = (int **)malloc(sizeof(int *) * (list->cmd_cnt + 1));
		if (!data->pipe_fd)
			return (parse_error(list, NULL, data, MALLOC_ERROR));
		i = 0;
		while (i < list->cmd_cnt)
		{
			data->pipe_fd[i] = (int *)malloc(sizeof(int) * (2));
			if (!(data->pipe_fd[i]))
				return (parse_error(list, NULL, data, MALLOC_ERROR));
			i++;
		}
		data->pipe_fd[i] = NULL;
	}
	data->input_fd = 0;
	data->output_fd = 1;
	data->list = list;
}
