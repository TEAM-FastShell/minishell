/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_signal.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youyoon <youyoon@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/23 23:47:04 by youyoon           #+#    #+#             */
/*   Updated: 2023/08/28 14:44:48 by youyoon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include "../../include/parse.h"

/* execute, heredoc 시그널 처리 필요 */
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

void	set_signal(void *int_handler, void *quit_handler)
{
	signal(SIGINT, int_handler);
	signal(SIGQUIT, quit_handler);
}
