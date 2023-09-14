/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seokklee <seokklee@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/07 19:46:06 by seokklee          #+#    #+#             */
/*   Updated: 2023/09/14 12:10:21 by seokklee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void		exec_export(t_data *data, char *export);
static int	is_exist(t_data *data, char	*export);
static char	*get_env_key(char *env);

void	builtin_export(t_data *data, t_node *node)
{
	if (node->pipe_type != NO_PIPE)
		return ;
	if (!node->cmd_args[1])
		builtin_env(data);
	else
	{
		if (ft_isdigit(node->cmd_args[1][0]) || node->cmd_args[1][0] == '=')
		{
			error_str_str_code(node, NON_VALID_ID, 1);
			return ;
		}
		if (node->cmd_args[2])
		{
			error_str_str_code(node, NON_VALID_ID, 1);
			return ;
		}
		exec_export(data, node->cmd_args[1]);
	}
	g_exit_status = 0;
}

void	exec_export(t_data *data, char *export)
{
	int		i;
	char	**new_envp;
	char	**tmp;

	if (is_exist(data, export))
		return ;
	i = 0;
	while (data->envp[i])
		i++;
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
	free_tab(tmp);
}

static int	is_exist(t_data *data, char	*export)
{
	int		i;
	char	*tmp;
	char	*del;

	i = 0;
	while (data->envp[i])
	{
		tmp = get_env_key(export);
		if (!ft_strncmp(data->envp[i], tmp, ft_strlen(tmp)))
		{
			free(tmp);
			del = data->envp[i];
			data->envp[i] = ft_strdup(export);
			free(del);
			return (1);
		}
		free(tmp);
		i++;
	}
	return (0);
}

static char	*get_env_key(char *env)
{
	char	*key;
	char	*tmp;

	tmp = ft_strchr(env, '=');
	key = ft_substr(env, 0, tmp - env);
	return (key);
}
