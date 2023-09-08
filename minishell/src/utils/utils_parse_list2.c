/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_parse_list2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youyoon <youyoon@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/07 19:47:15 by seokklee          #+#    #+#             */
/*   Updated: 2023/09/08 16:40:50 by youyoon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parse.h"

static int	count_pipe_type(t_double_list *list)
{
	int		cnt;
	t_node	*cur;

	cnt = 0;
	cur = list->head;
	while (cur)
	{
		if (cur->pipe_type > 0)
			cnt++;
		cur = cur->next;
	}
	return (cnt);
}

void	set_pipe_type(t_double_list *list)
{
	t_node	*cur;
	int		pipe_cnt;

	pipe_cnt = count_pipe_type(list);
	if (pipe_cnt > 0)
	{
		cur = list->head;
		while (cur->pipe_type == 0)
			cur = cur->next;
		if (cur->pipe_type == RW_PIPE)
			cur->pipe_type = W_PIPE;
		list->tail->pipe_type = R_PIPE;
	}
}

void	set_list_idx(t_double_list *list)
{
	t_node	*cur;
	int		i;

	i = 0;
	cur = list->head;
	while (cur)
	{
		if (cur->redir_type == NO_REDIR)
		{
			cur->idx = i;
			i++;
		}
		cur = cur->next;
	}
}

char	*get_envv(char *envp[], char *envv)
{
	char	*address;
	char	c;

	envv++;
	while (*envp && *envv)
	{
		if (!ft_strncmp(*envp, envv, ft_strlen(envv)))
		{
			address = *envp + ft_strlen(envv);
			c = *address;
			if (c == '=')
				return (*envp + ft_strlen(envv) + 1);
		}
		envp++;
	}
	return ("");
}

void	change_env(t_node *node, t_parse *parse)
{
	int		i;
	char	*tmp;
	char	*env_val;

	i = -1;
	while (node->cmd_args[++i])
	{
		if (!ft_strncmp(node->cmd_args[i], "$?", ft_strlen(node->cmd_args[i])))
			continue ;
		if (ft_strchr(node->cmd_args[i], '$') && \
			!ft_strchr(node->cmd_args[i], '\'') && \
			ft_strlen(node->cmd_args[i]) > 1)
		{
			tmp = node->cmd_args[i];
			env_val = get_envv(parse->env, node->cmd_args[i]);
			node->cmd_args[i] = ft_strdup(env_val);
			free(tmp);
		}
	}
}
