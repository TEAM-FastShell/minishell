/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_unset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seokklee <seokklee@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/07 19:46:10 by seokklee          #+#    #+#             */
/*   Updated: 2023/09/07 19:46:11 by seokklee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
			error_str_str_code(node, NON_VALID_ID, 1);
		exec_unset(data, node->cmd_args[1]);
	}
	g_exit_status = 0;
}

static void	exec_unset(t_data *data, char *unset)
{
	int		i;
	int		flag;
	char	*tmp;

	flag = 0;
	i = 0;
	while (data->envp[i + 1])
	{
		if (match_key(data->envp[i], unset))
		{
			tmp = data->envp[i];
			data->envp[i] = data->envp[i + 1];
			data->envp[i + 1] = tmp;
			flag = 1;
		}
		i++;
	}
	if (flag || match_key(data->envp[i], unset))
	{
		free(data->envp[i]);
		data->envp[i] = NULL;
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
