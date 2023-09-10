/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_parse2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seokklee <seokklee@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/07 19:47:21 by seokklee          #+#    #+#             */
/*   Updated: 2023/09/10 19:52:47 by seokklee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parse.h"

int	count_word(char *str)
{
	int	cnt;

	cnt = 0;
	while (*str)
	{
		while (*str == ' ' || (9 <= *str && *str <= 13))
			str++;
		if (*str && !(*str == ' ' || (9 <= *str && *str <= 13)))
		{
			cnt++;
			while (*str && !(*str == ' ' || (9 <= *str && *str <= 13)))
				str++;
		}
	}
	return (cnt);
}

void	init_data_before_start(t_data **data, char **envp)
{
	*data = (t_data *) malloc(sizeof(t_data));
	if (!(*data))
		return (parse_error(NULL, NULL, NULL, MALLOC_ERROR));
	(*data)->list = NULL;
	(*data)->pipe_fd = NULL;
	(*data)->envp = copy_env(envp);
	if (!(*data)->envp)
		return (parse_error(NULL, NULL, (*data), MALLOC_ERROR));
}

int	check_env_char(char c)
{
	if ('a' <= c && c <= 'z')
		return (1);
	else if ('A' <= c && c <= 'Z')
		return (1);
	else if (c == '_')
		return (1);
	else if (c == '?')
		return (1);
	else if ('0' <= c && c <= '9')
		return (1);
	return (0);
}

char	*change_to_env(t_parse *parse, char *input, int start, int end)
{
	char	*env_str;
	int		i;
	int		len;
	char	*ret;

	i = 0;
	len = end - start + 2;
	env_str = (char *) malloc(sizeof(char) * (end - start + 3));
	if (!env_str)
		return (NULL);
	env_str[0] = '$';
	while (++i < len)
		env_str[i] = input[start++];
	env_str[i] = '\0';
	ret = ft_strdup(get_envv(parse->env, env_str));
	free(env_str);
	return (ret);
}

void	put_env_to_buff(t_parse *parse, char *env, size_t input_len)
{
	char	*tmp_buff;

	tmp_buff = ft_strjoin(parse->buff, env);
	free(parse->buff);
	parse->b_idx = 0;
	parse->buff = (char *) ft_calloc(input_len + \
				ft_strlen(env) + 1, sizeof(char));
	ft_strlcpy(parse->buff, tmp_buff, ft_strlen(tmp_buff) + 1);
	parse->b_idx = (int) ft_strlen(tmp_buff);
	free(tmp_buff);
}
