/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_signal.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youyoon <youyoon@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/23 23:47:04 by youyoon           #+#    #+#             */
/*   Updated: 2023/08/26 19:34:25 by youyoon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include "../../include/parse.h"

void	signal_handler(int signo)
{
	if (signo == SIGINT)
	{
		ft_putchar_fd('\n', STDOUT);
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
		g_exit_status = 1;
	}
	else if (signo == SIGQUIT)
	{
		rl_on_new_line();
		rl_redisplay();
	}
}

void	set_signal(void)
{
	signal(SIGINT, signal_handler);
	signal(SIGQUIT, signal_handler);
}
