/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_pwd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seokklee <seokklee@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/07 19:46:08 by seokklee          #+#    #+#             */
/*   Updated: 2023/09/07 19:46:09 by seokklee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	builtin_pwd(void)
{
	char	*pwd;

	pwd = getcwd(NULL, 2048);
	printf("%s\n", pwd);
	free(pwd);
	pwd = NULL;
	g_exit_status = 0;
}
