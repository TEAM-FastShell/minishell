/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seokklee <seokklee@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/28 13:35:39 by seokklee          #+#    #+#             */
/*   Updated: 2023/08/28 13:35:40 by seokklee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void		exec_export(t_data *data, char *export);
static int	is_exist(t_data *data, char	*export);

void	builtin_export(t_data *data, t_node *node)
{
	if (node->pipe_type != NO_PIPE)
		return ;
	if (!node->cmd_args[1])
		builtin_env(data, node);
	else
	{
		if (ft_isdigit(node->cmd_args[1][0]) || node->cmd_args[1][0] == '=')
			error_str_str_code(node, NON_VALID_ID, 1);
		exec_export(data, node->cmd_args[1]);
	}
	g_exit_status = 0;
}/*unset export 인자 여러개*/

void	exec_export(t_data *data, char *export)
{
	int		i;
	char	**new_envp;
	char	**tmp;

	if (is_exist(data, export))
		return ;
	new_envp = (char **)malloc(sizeof(char *) * (i + 2));
	if (!new_envp)
		g_exit_status = 1;
	i = 0;
	while (data->envp[i])
	{
		new_envp[i] = ft_strdup(data->envp[i]);
		i++;
	}
	new_envp[i] = ft_strdup(export);
	new_envp[++i] = NULL;
	tmp = data->envp;
	data->envp = new_envp;
	free_envp(tmp);
}

static int	is_exist(t_data *data, char	*export)
{
	int		i;

	i = 0;
	while (data->envp[i])
	{
		if (!ft_strncmp(data->envp[i], export, ft_strlen(export)))
		{
			data->envp[i] = ft_strdup(export);
			return (1);
		}
		i++;
	}
	return (0);
}
