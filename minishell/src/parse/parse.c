/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seokklee <seokklee@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/07 19:46:39 by seokklee          #+#    #+#             */
/*   Updated: 2023/09/14 19:59:18 by seokklee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parse.h"

static int	no_quote(t_double_list *list, t_parse *parse, char *input, int *i);

static void	set_quote(t_parse *parse, char *input, int **i)
{
	int		dollar_start;
	char	*dollar_to_env;

	dollar_to_env = NULL;
	if (parse->quote == input[**i])
		parse->quote = 0;
	else if ((!parse->quote || parse->quote == '\"') && input[**i] == '$')
	{
		dollar_start = ++(**i);
		if (input[dollar_start] == '?')
		{
			dollar_to_env = ft_itoa(g_exit_status);
			put_env_to_buff(parse, dollar_to_env, ft_strlen(input));
			free(dollar_to_env);
			return ;
		}
		while (input[**i] && check_env_char(input[**i]))
			(**i)++;
		dollar_to_env = change_to_env(parse, input, dollar_start, --(**i));
		put_env_to_buff(parse, dollar_to_env, ft_strlen(input));
		free(dollar_to_env);
	}
	else if (!parse->quote && (input[**i] == '\'' || input[**i] == '\"'))
		parse->quote = input[**i];
}

static int	check_quote(t_parse *parse, char c, char next)
{
	if (parse->quote == c)
		return (1);
	else if ((!parse->quote || parse->quote == '\"') \
	&& c == '$' && check_env_char(next))
		return (1);
	else if (!parse->quote && (c == '\'' || c == '\"'))
		return (1);
	return (0);
}

int	parse_char(t_double_list *list, t_parse *parse, char *input, int *i)
{
	int	ret;

	ret = SUCCESS;
	if (check_quote(parse, input[*i], input[*i + 1]))
		set_quote(parse, input, &i);
	else if (!parse->quote && ft_strchr(" |><", input[*i]))
		ret = no_quote(list, parse, input, i);
	else
		parse->buff[parse->b_idx++] = input[*i];
	return (ret);
}

static int	no_quote(t_double_list *list, t_parse *parse, char *input, int *i)
{
	if (input[*i] == ' ')
	{
		put_buff_to_cmd(parse);
		if (parse->cmd[0] && parse->cmd[0][0] != 0 && parse->redir_type != 0)
			return (add_node(list, parse));
	}
	else if (input[*i] == '|')
	{
		put_buff_to_cmd(parse);
		if (parse->cmd[0] && parse->cmd[0][0] != 0)
			if (add_node(list, parse) < 0)
				return (ERROR);
		if (check_pipe_error(parse, list) < 0)
			return (ERROR);
	}
	else
	{
		if (parse->cmd[0] && parse->cmd[0][0] != 0)
			if (add_node(list, parse) < 0)
				return (ERROR);
		parse->redir_type = check_redir(input[*i], input[*i + 1]);
		if (parse->redir_type == A_REDIR || parse->redir_type == H_REDIR)
			(*i)++;
	}
	return (SUCCESS);
}

void	parser(char *input, t_data *data, t_double_list *list, t_parse *parse)
{
	int		i;
	int		token_cnt;

	token_cnt = count_word(input);
	init_list(list);
	init_parse(parse, token_cnt, data, (int) ft_strlen(input));
	i = -1;
	while (input[++i])
	{
		if (parse_char(list, parse, input, &i) < 0)
		{
			free(input);
			return (parse_error(list, parse, NULL, SYNTAX_ERROR));
		}
	}
	free(input);
	if (parse->buff[0])
		put_buff_to_cmd(parse);
	if (parse->quote != 0 || add_node(list, parse) < 0)
		return (parse_error(list, parse, NULL, SYNTAX_ERROR));
	if (list->cmd_cnt >= 126)
		return (parse_error(list, parse, NULL, PARSE_TOO_MANY_ARG));
	set_pipe_type(list);
	set_list_idx(list);
	parse_error(NULL, parse, NULL, NULL);
}
