/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seokklee <seokklee@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/07 19:47:28 by seokklee          #+#    #+#             */
/*   Updated: 2023/09/12 12:05:14 by seokklee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parse.h"

int	is_whitespace(char *str)
{
	int	i;
	int	space;

	i = 0;
	space = 0;
	if ((int) ft_strlen(str) == 0)
		return (1);
	while (str[i])
	{
		if (str[i] == '\r' || str[i] == '\v' || \
				str[i] == '\t' || str[i] == '\f')
			return (1);
		else if (str[i] == ' ')
			space++;
		i++;
	}
	if ((int) ft_strlen(str) == space)
		return (1);
	return (0);
}

char	*get_envv_data(char *envp[], char *envv)
{
	while (*envp)
	{
		if (!ft_strncmp(*envp, envv, ft_strlen(envv)))
			return (*envp + ft_strlen(envv) + 1);
		envp++;
	}
	return ("");
}

void	free_pipe_fd(t_data *data)
{
	int	i;

	if (!data->pipe_fd)
		return ;
	i = 0;
	while (i < data->list->cmd_cnt + 1)
	{
		free(data->pipe_fd[i]);
		data->pipe_fd[i] = NULL;
		i++;
	}
	free(data->pipe_fd);
	data->pipe_fd = NULL;
}

void	put_buff_to_cmd(t_parse *parse)
{
	if (parse->buff[0] == 0)
		return ;
	parse->cmd[parse->c_idx] = ft_strdup(parse->buff);
	parse->cmd[parse->c_idx + 1] = NULL;
	parse->c_idx++;
	ft_bzero(parse->buff, ft_strlen(parse->buff) + 1);
	parse->b_idx = 0;
}

int	check_pipe_error(t_parse *parse, t_double_list *list)
{
	if (list->cnt > 0 && list->tail->pipe_type != NO_PIPE \
		&& parse->buff[0] == 0)
		return (ERROR);
	if (list->cnt == 0)
		return (ERROR);
	list->tail->pipe_type = RW_PIPE;
	return (SUCCESS);
}
