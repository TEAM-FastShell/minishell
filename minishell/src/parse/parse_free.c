/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_free.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youyoon <youyoon@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/17 17:13:46 by youyoon           #+#    #+#             */
/*   Updated: 2023/08/28 14:04:58 by youyoon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include "../../include/parse.h"

void	free_parse(t_parse *parse)
{
	int	i;

	if (!parse)
		return ;
	i = 0;
	while (parse->cmd[i])
		free(parse->cmd[i++]);
	i = -1;
	while (parse->env[++i])
		free(parse->env[i]);
	free(parse->cmd);
	free(parse->buff);
	free(parse->env);
	parse = NULL;
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
	list = NULL;
}
