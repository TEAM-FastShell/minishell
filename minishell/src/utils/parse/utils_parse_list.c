/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_parse_list.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youyoon <youyoon@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/17 17:01:30 by youyoon           #+#    #+#             */
/*   Updated: 2023/08/23 18:17:50 by youyoon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"
#include "../../../include/parse.h"

static void	copy_strings(char ***dest, char **src, int len, t_parse *parse)
{
	int	i;

	*dest = (char **) ft_calloc(len + 1, sizeof(char *));
	if (!(*dest))
		return ;
	i = 0;
	while (i < len)
	{
		if (ft_strchr(src[i], '$') && !ft_strchr(src[i], '\''))
			(*dest)[i] = find_env(src[i], parse->env);
		if (!(*dest)[i])
			(*dest)[i] = ft_strdup(src[i]);
		i++;
	}
	(*dest)[i] = NULL;
}

t_node	*make_node(t_parse *parse)
{
	t_node	*new_node;

	new_node = (t_node *) malloc(sizeof(t_node));
	if (!(new_node))
		return (NULL);
	new_node->prev = NULL;
	new_node->next = NULL;
	copy_strings(&(new_node->cmd_args), parse->cmd, parse->c_idx, parse);
	new_node->pipe_type = parse->pipe_type;
	new_node->redir_type = parse->redir_type;
	new_node->pid = 0;
	return (new_node);
}

int	add_node(t_double_list *list, t_parse *parse)
{
	t_node	*new_node;
	int		i;

	if ((parse->buff[0]))
		put_buff_to_cmd(parse);
	if (!(parse->cmd[0]) && (parse->pipe_type > 0 || parse->redir_type > 0))
		return (ERROR);
	else if (!(parse->cmd[0]))
		return (ERROR);
	new_node = make_node(parse);
	ms_listadd_back(list, new_node);
	i = 0;
	while (parse->cmd[i])
	{
		ft_bzero(parse->cmd[i], ft_strlen(parse->cmd[i]) + 1);
		i++;
	}
	parse->quote = 0;
	parse->c_idx = 0;
	parse->b_idx = 0;
	parse->pipe_type = NO_PIPE;
	parse->redir_type = NO_REDIR;
	return (SUCCESS);
}

void	ms_listadd_back(t_double_list *list, t_node *new_node)
{
	if (!list || !new_node)
		return ;
	if (list->cnt == 0)
	{
		list->head = new_node;
		list->tail = new_node;
	}
	else if (new_node->redir_type > 0)
		ms_listadd_back_redir(list, new_node);
	else
	{
		list->tail->next = new_node;
		new_node->prev = list->tail;
		list->tail = new_node;
	}
	list->cnt++;
	if (new_node->redir_type == 0)
		list->cmd_cnt++;
}

void	ms_listadd_back_redir(t_double_list *list, t_node *new_node)
{
	t_node	*cur;

	cur = list->tail;
	while (cur->prev && (cur->redir_type == 0 && cur->pipe_type == 0))
		cur = cur->prev;
	if (cur == list->head && (cur->redir_type == 0 && cur->pipe_type == 0))
	{
		new_node->next = cur;
		cur->prev = new_node;
		list->head = new_node;
	}
	else
	{
		new_node->prev = cur;
		new_node->next = cur->next;
		cur->next->prev = new_node;
		cur->next = new_node;
	}
}
