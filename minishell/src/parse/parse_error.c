/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youyoon <youyoon@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/16 16:01:57 by youyoon           #+#    #+#             */
/*   Updated: 2023/08/29 14:47:51 by youyoon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include "../../include/parse.h"

/*
	malloc이 안됐을 때 에러 처리 생각
*/
void	parse_error(t_double_list *list, t_parse *parse, \
		t_data *data, char *error_msg)
{
	int	i;

	if (list)
		free_list(list);
	if (parse)
		free_parse(parse);
	if (data)
	{
		i = -1;
		while (data->pipe_fd[++i])
			free(data->pipe_fd[i]);
		free(data->pipe_fd);
		i = -1;
		while (data->envp[++i])
			free(data->envp[i]);
		i = -1;
		while (data->path_tab[++i])
			free(data->path_tab[i]);
		free(data->path_tab);
		free(data->envp);
		free(data);
	}
	if (error_msg)
		ft_putendl_fd(error_msg, STDERR);
	return ;
}
