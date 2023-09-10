/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seokklee <seokklee@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/07 19:46:30 by seokklee          #+#    #+#             */
/*   Updated: 2023/09/10 19:53:01 by seokklee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parse.h"

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
		free(data->envp);
		free(data);
	}
	if (error_msg)
		ft_putendl_fd(error_msg, STDERR);
	return ;
}
