/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youyoon <youyoon@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/24 13:48:47 by youyoon           #+#    #+#             */
/*   Updated: 2023/08/26 19:30:23 by youyoon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/parse.h"
#include "../include/minishell.h"

void check()
{
	system("leaks minishell");
}

int	main(int argc, char *argv[], char *envp[])
{
	char			*input;

	while (argc && argv)
	{
		//system("leaks minishell");
		set_signal();
		input = readline("Minishell$ ");
		if (input == NULL)
		{
			printf("exit\n");
			break ;
		}
		if (*input != '\0')
		{
			add_history(input);
			if (!is_whitespace(input))
				parser(input, envp);
		}
		free(input);
	}
	free(input);
	return (0);
}
