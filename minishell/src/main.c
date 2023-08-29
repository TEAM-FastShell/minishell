/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youyoon <youyoon@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/24 13:48:47 by youyoon           #+#    #+#             */
/*   Updated: 2023/08/29 15:11:55 by youyoon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/parse.h"
#include "../include/minishell.h"

int	main(int argc, char *argv[], char *envp[])
{
	char			*input;
	t_double_list	list;
	t_parse			parse;
	t_data			data;

	init_data_before_start(&data, envp);
	while (argc && argv)
	{
		set_signal();
		input = readline("Minishell$ ");
		if (input == NULL)
		{
			printf("exit\n");
			break ; /* exit g_status 처리 */
		}
		if (*input != '\0')
		{
			add_history(input);
			if (!is_whitespace(input))
			{
				parser(input, envp, &list, &parse);
				if (list.head && parse.env)
				{	
					init_in_while_data(&data, &list);
					execute(&data);
				}
			}
		}
		free(input);
		/* 마지막 모두 free */
	}
	return (0);
}
