/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_signal.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youyoon <youyoon@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/23 23:47:04 by youyoon           #+#    #+#             */
/*   Updated: 2023/08/24 13:14:49 by youyoon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include "../../include/parse.h"

void	signal_handler(int signo)
{
	pid_t	pid;
	int		stat;

	pid = waitpid(-1, &stat, WNOHANG);
	if (signo == SIGINT)
	{
		if (pid == -1)
		{
			ft_putendl_fd("pid -1", STDOUT);
		}
		else
		{
			ft_putchar_fd('\n', STDOUT);
		}
	}
}

void	set_signal(void)
{
	signal(SIGINT, signal_handler);
	signal(SIGQUIT, SIG_IGN);
}
