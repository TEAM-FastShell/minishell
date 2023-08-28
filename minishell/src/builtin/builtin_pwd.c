/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_pwd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youyoon <youyoon@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/28 13:35:41 by seokklee          #+#    #+#             */
/*   Updated: 2023/08/28 15:30:01 by youyoon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	builtin_pwd(t_data *data)
{
	char	*pwd;

	pwd = getcwd(NULL, 2048);
	ft_putendl_fd(pwd, data->output_fd);
	free(pwd);
	g_exit_status = 0;
}
