/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_parse.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youyoon <youyoon@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/16 15:52:10 by youyoon           #+#    #+#             */
/*   Updated: 2023/08/29 19:15:27 by youyoon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"
#include "../../../include/parse.h"

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

void	init_parse(t_parse *parse, int token_cnt, int input_len, char **env)
{
	parse->cmd = (char **) ft_calloc(token_cnt + 1, sizeof(char *));
	if (!parse->cmd)
		return (parse_error(NULL, NULL, NULL, MALLOC_ERROR));
	parse->buff = (char *) ft_calloc(input_len + 1, sizeof(char));
	if (!parse->buff)
		return (parse_error(NULL, parse, NULL, MALLOC_ERROR));
	parse->env = copy_env(env);
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
	if (list->cmd_cnt > 1)
	{
		data->pipe_fd = (int **)malloc(sizeof(int *) * (list->cmd_cnt));
		if (!data->pipe_fd)
			return (parse_error(list, NULL, data, MALLOC_ERROR));
		i = -1;
		while (++i < list->cmd_cnt)
		{
			data->pipe_fd[i] = (int *)malloc(sizeof(int) * (2));
			if (!data->pipe_fd[i])
				return (parse_error(list, NULL, data, MALLOC_ERROR));
		}
		data->pipe_fd[i - 1] = NULL;
	}/*fix*/
	data->input_fd = 0;
	data->output_fd = 1;
	data->list = list;
}
