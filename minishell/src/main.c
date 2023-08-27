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

int	main(int argc, char *argv[], char *envp[])
{
	char			*input;
	t_double_list	list;
	t_parse			parse;
	t_data			*data;

	while (argc && argv)
	{
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
			{	
				parser(input, envp, &list, &parse);
				if (list.cnt > 0 && parse.env)
					init_data(&data, &list, &parse);
				if (data)
					parse_error(&list, &parse, data, NULL);
			}
		}
		free(input);
	}
	return (0);
}

// /* 출력 테스트 */
				// t_node *cur = data->list->head;
				// while (cur)
				// {
				// 	int i = 0;
				// 	printf("|");
				// 	while (cur->cmd_args[i])
				// 	{	printf(" %s, ", cur->cmd_args[i]); i++; }
				// 	printf(" red %d pipe %d idx %d | -> ", cur->redir_type, cur->pipe_type, cur->idx);
				// 	cur = cur->next;
				// }
				// printf("\n");
				// /* **** */
