/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_free.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youyoon <youyoon@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/17 17:13:46 by youyoon           #+#    #+#             */
/*   Updated: 2023/08/26 19:59:22 by youyoon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include "../../include/parse.h"

void	free_parse(t_parse *parse)
{
	int	i;

	printf("free parse\n");
	if (!parse)
		return ;
	i = 0;
	while (parse->cmd[i])
		free(parse->cmd[i++]);
	free(parse->cmd);
	free(parse->buff);
	free(parse);
}

void	free_list(t_double_list *list)
{
	t_node	*cur;
	t_node	*del;
	int		i;

	if (!list)
		return ;
	cur = list->head;
	while (cur)
	{
		del = cur;
		cur = cur->next;
		i = 0;
		while (del->cmd_args[i])
		{
			free(del->cmd_args[i]);
			i++;
		}
		free(del->cmd_args);
		free(del);
	}
	free(list);
	printf("free_list\n");
}

void	free_data(t_data *data)
{
	int	i;

	if (!data)
		return ;
	i = -1;
	while (data->envp[++i])
		free(data->envp[i]);
	free(data->envp);
	i = -1;
	while (++i < 2)
		free(data->pipe_fd[i]);
	free(data->pipe_fd);
	free(data);
	printf("free_data\n");
}
