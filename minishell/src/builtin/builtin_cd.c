/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seokklee <seokklee@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/07 19:45:57 by seokklee          #+#    #+#             */
/*   Updated: 2023/09/10 14:43:22 by seokklee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	builtin_cd_home(t_data *data, t_node *node);
static void	set_pwds(t_data *data);

void	builtin_cd(t_data *data, t_node *node)
{
	char	*path;

	path = NULL;
	if (node->cmd_args[1] == NULL \
	|| !ft_strncmp(node->cmd_args[1], "~", ft_strlen(node->cmd_args[1])))
		builtin_cd_home(data, node);
	else
	{
		path = node->cmd_args[1];
		if (path[0] == '~')
			path = ft_strjoin(get_envv_data(data->envp, "HOME"), path + 1);
		if (chdir(path) < 0)
			error_str_str_code(node, NO_FILE_DIR, 1);
		set_pwds(data);
		if (path[0] == '~')
			free(path);
	}
	g_exit_status = 0;
}

static void	builtin_cd_home(t_data *data, t_node *node)
{
	char	*home;

	home = get_envv_data(data->envp, "HOME");
	if (chdir(home) < 0)
	{
		error_str_code(node, HOME_NOT_SET, 1);
		exit(g_exit_status);
	}
	set_pwds(data);
}

void	set_pwds(t_data *data)
{
	char	*pwd;
	char	*oldpwd;
	char	*tmp;

	tmp = (char *)malloc(sizeof(char) * 2048);
	pwd = ft_strjoin("PWD=", getcwd(tmp, 2048));
	oldpwd = ft_strjoin("OLDPWD=", get_envv_data(data->envp, "PWD"));
	exec_export(data, pwd);
	exec_export(data, oldpwd);
	free(tmp);
	free(pwd);
	free(oldpwd);
}
