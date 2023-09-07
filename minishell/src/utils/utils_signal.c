/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_signal.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seokklee <seokklee@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/07 19:47:23 by seokklee          #+#    #+#             */
/*   Updated: 2023/09/07 19:47:24 by seokklee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parse.h"

void	signal_handler(int signo)
{
	if (signo == SIGINT)
	{
		printf("\n");
		g_exit_status = 1;
	}
	rl_replace_line("", 1);
	if (rl_on_new_line() == -1)
		exit(1);
	rl_redisplay();
}

void	execute_sigint_handler(int signo)
{
	if (signo == SIGINT)
		printf("^C\n");
}

void	execute_sigquit_handler(int signo)
{
	if (signo == SIGQUIT)
		printf("^\\Quit: 3\n");
}

void	heredoc_sigint_handler(int signo)
{
	if (signo == SIGINT)
	{
		close(0);
		printf("\n");
		g_exit_status = 1;
	}
}

void	set_signal(void *int_handler, void *quit_handler)
{
	signal(SIGINT, int_handler);
	signal(SIGQUIT, quit_handler);
}
