/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_signal.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seokklee <seokklee@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/23 23:47:04 by youyoon           #+#    #+#             */
/*   Updated: 2023/08/28 13:36:19 by seokklee         ###   ########.fr       */
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
