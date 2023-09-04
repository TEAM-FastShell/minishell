/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_unset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seokklee <seokklee@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/28 13:35:45 by seokklee          #+#    #+#             */
/*   Updated: 2023/09/04 15:38:17 by seokklee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void	exec_unset(t_data *data, char *unset);
static int	match_key(char *str, char *unset);

void	builtin_unset(t_data *data, t_node *node)
{
	if (node->pipe_type != NO_PIPE || !node->cmd_args[1])
		return ;
	else
	{
		if (ft_isdigit(node->cmd_args[1][0])
		|| ft_strchr(node->cmd_args[1], '='))
			error_str_str_code(data, node, NON_VALID_ID, 1);
		exec_unset(data, node->cmd_args[1]);
	}
	data->exit_status = 0;
}

static void	exec_unset(t_data *data, char *unset)
{
	int		i;
	int		flag;
	char	*tmp;

	flag = 0;
	i = 0;
	while (g_envp[i + 1])
	{
		if (match_key(g_envp[i], unset))
		{
			tmp = g_envp[i];
			g_envp[i] = g_envp[i + 1];
			g_envp[i + 1] = tmp;
			flag = 1;
		}
		i++;
	}
	if (flag || match_key(g_envp[i], unset))
	{
		free(g_envp[i]);
		g_envp[i] = NULL;
	}
}

static int	match_key(char *envp, char *unset)
{
	int		i;

	i = 0;
	while (envp[i] && unset[i] && (envp[i] == unset[i]) && envp[i] != '=')
		i++;
	if (envp[i] == '=' && unset[i] == '\0')
		return (1);
	return (0);
}
