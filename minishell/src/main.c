/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youyoon <youyoon@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/24 13:48:47 by youyoon           #+#    #+#             */
/*   Updated: 2023/08/24 17:38:32 by youyoon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/parse.h"
#include "../include/minishell.h"

void	show_prompt(void)
{
	ft_putstr_fd("Minishell$  ", STDOUT);
}

// void check()
// {
// 	system("leaks minishell");
// }

int	main(int argc, char *argv[], char *envp[])
{
	char	*input;

	(void) envp;

	set_signal();
	while (argc && argv)
	{
		show_prompt();
		input = readline("");
		if (input == NULL)
		{
			printf("exit\n");
			break ;
		}
		if (*input != '\0')
		{
			add_history(input);
			if (!is_whitespace(input)) {
				parser(input);
			}
		}
		free(input);
	}
	return (0);
}







