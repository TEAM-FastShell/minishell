#include "../../include/minishell.h"
#include "../../include/parse.h"

/**
 * quote가 double로 열려있을 때 $가 들어오면 : num, alpha, '_'가 아닌 문자가 나올 때까지 인풋을 탐색
 * 탐색이 끝나면 달러가 붙은 문자열을 환경 변수에서 찾음
 * 있으면 문자열을 리턴해서 버퍼에 붙임
 *
 * 쿼트가 열려있지 않을 때 쿼트가 들어왔으면 : 싱글은 버퍼에 담고, 더블은 버퍼에 담지 않음
 * 쿼트가 열려있을 때 쿼트와 같은 문자가 들어오면 쿼트 닫음
*/
/* 줄 25*/
static void	set_quote(t_parse *parse, char *input, int **i)
{
	int		dollar_start;
	char	*dollar_to_env;

	dollar_to_env = NULL;
	if (parse->quote == input[**i])
	{
		parse->quote = 0;
		if (input[**i] == '\'')
			parse->buff[parse->b_idx++] = input[**i];
	}
	else if ((!parse->quote || parse->quote == '\"') && input[**i] == '$')
	{
		dollar_start = ++(**i);
		if (input[dollar_start] == '?')
		{
			dollar_to_env = ft_itoa(g_exit_status);
			put_env_to_buff(parse, dollar_to_env);
			free(dollar_to_env);
			return ;
		}
		while (input[**i] && check_env_char(input[**i]))
			(**i)++;
		dollar_to_env = change_to_env(parse, input, dollar_start, --(**i));
		put_env_to_buff(parse, dollar_to_env);
		free(dollar_to_env);
	}
	else if (!parse->quote && (input[**i] == '\'' || input[**i] == '\"'))
	{
		parse->quote = input[**i];
		if (input[**i] == '\'')
			parse->buff[parse->b_idx++] = input[**i];
	}
}

void	put_buff_to_cmd(t_parse *parse)
{
	if (!(parse->buff[0]))
		return ;
	parse->cmd[parse->c_idx] = ft_strdup(parse->buff);
	parse->cmd[parse->c_idx + 1] = NULL;
	parse->c_idx++;
	ft_bzero(parse->buff, ft_strlen(parse->buff) + 1);
	parse->b_idx = 0;
}

/* double quote가 열려있을 때 인풋값이 달러이면 트루와 동시에 함수에 들어감
 * 아직 열리지 않은 상태에서 input이 quote이면 함수로 들어가서 버퍼에 저장해야하니까 true
 * 쿼트가 열려있을 때 같은 문자가 들어오면 닫아야 하므로, true 리턴 후 함수로 들어감
*/
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

/* 25줄 맞춰서 분할 필요*/
int	parse_char(t_double_list *list, t_parse *parse, char *input, int *i)
{
	int	ret;

	ret = SUCCESS;
	if (check_quote(parse, input[*i], input[*i + 1]))
		set_quote(parse, input, &i);
	else if (!parse->quote && input[*i] == ' ')
		put_buff_to_cmd(parse);
	else if (!parse->quote && input[*i] == ';')
		ret = ERROR;
	else if (!parse->quote && input[*i] == '|')
	{
		ret = add_node(list, parse);
		if (ret > 0)
			list->tail->pipe_type = RW_PIPE;
	}
	else if (!parse->quote && ft_strchr("><", input[*i]))
	{
		if (parse->cmd[0] && parse->cmd[0][0] != 0)
			ret = add_node(list, parse);
		parse->redir_type = check_redir(input[*i], input[*i + 1]);
		if (parse->redir_type == A_REDIR || parse->redir_type == H_REDIR)
			(*i)++;
	}
	else
		parse->buff[parse->b_idx++] = input[*i];
	return (ret);
}

void	parser(char *input_tmp, t_data *data, \
				t_double_list *list, t_parse *parse)
{
	int				i;
	int				token_cnt;
	char			*input;

	input = ft_strtrim(input_tmp, " ");
	token_cnt = count_word(input);
	init_list(list);
	init_parse(parse, token_cnt, (int) ft_strlen(input), data);
	i = -1;
	while (input[++i])
	{
		if (parse_char(list, parse, input, &i) < 0)
			return (parse_error(list, parse, NULL, SYNTAX_ERROR));
	}
	if (parse->buff[0])
		put_buff_to_cmd(parse);
	if (parse->quote != 0)
		return (parse_error(list, parse, NULL, SYNTAX_ERROR));
	if (add_node(list, parse) < 0)
		return (parse_error(list, parse, NULL, SYNTAX_ERROR));
	set_pipe_type(list);
	set_list_idx(list);
	parse_error(NULL, parse, NULL, NULL);
	free(input);
}
