/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_parse2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youyoon <youyoon@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/29 12:30:41 by youyoon           #+#    #+#             */
/*   Updated: 2023/08/29 14:03:37 by youyoon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"
#include "../../../include/parse.h"

void	init_data_before_start(t_data *data, char **envp)
{
	data = (t_data *) malloc(sizeof(t_data));
	if (!data)
		return (parse_error(NULL, NULL, data, MALLOC_ERROR));
	data->list = NULL;
	data->path_tab = NULL;
	data->pipe_fd = NULL;
	data->envp = copy_env(envp);
	if (!data->envp)
		return (parse_error(NULL, NULL, data, MALLOC_ERROR));
}
