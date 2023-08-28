/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_parse.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youyoon <youyoon@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/16 15:52:10 by youyoon           #+#    #+#             */
/*   Updated: 2023/08/28 16:42:20 by youyoon          ###   ########.fr       */
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
	i = -1;
	while (env[++i])
		ret[i] = ft_strdup(env[i]);
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

void	init_data(t_data **data_ptr, t_double_list *list, t_parse *parse)
{
	int		i;
	t_data	*data;

	if (!list->head || !parse->env)
		return ;
	*data_ptr = (t_data *) malloc(sizeof(t_data));
	if (!(*data_ptr))
		return (parse_error(list, parse, *data_ptr, MALLOC_ERROR));
	data = *data_ptr;
	data->envp = parse->env;
	i = -1;
	if (list->cnt > 1)
	{
		while (++i < 2)
		{
			data->pipe_fd[i] = (int *)malloc(sizeof(int) * (list->cmd_cnt - 1));
			if (!data->pipe_fd[i])
				return (parse_error(list, parse, data, MALLOC_ERROR));
		}
	}
	data->input_fd = 0;
	data->output_fd = 1;
	data->list = list;
}
