/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seokklee <seokklee@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/24 13:48:47 by youyoon           #+#    #+#             */
/*   Updated: 2023/09/04 15:31:33 by seokklee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/parse.h"
#include "../include/minishell.h"

//int data->exit_status = 0;

static int	set_main(void)
{
	struct termios	term;
	int				res;

	res = 0;
	res += tcgetattr(STDIN_FILENO, &term);
	term.c_lflag &= ~(ECHOCTL);
	res += tcsetattr(STDIN_FILENO, TCSANOW, &term);
	set_signal(signal_handler, SIG_IGN);
	return (res);
}

/* SIGTERM signal handler */
static void	print_prompt(char **input)
{
	free(*input);
	printf("exit\n");
	exit(0);
}

/* 최종 사용한 struct 모두 free 구현 필요 */
static void	prompt_while(t_data *data, t_double_list *list, \
				t_parse *parse, char **envp)
{
	char	*input;

	while (1)
	{
		input = readline("bash$ ");
		if (!input)
			print_prompt(&input);
		else if (*input == '\0')
			data->exit_status = 0;
		else
		{
			add_history(input);
			if (!is_whitespace(input))
			{
				parser(input, envp, list, parse);
				if (list->head)
				{
					init_in_while_data(data, list);
					execute(data);
				}
			}
		}
		free(input);
	}
}

/* 최종 사용한 struct 모두 free 구현 필요 */
int	main(int argc, char *argv[], char *envp[])
{
	t_double_list	list;
	t_parse			parse;
	t_data			*data;

	if (argc && argv)
	{
		init_data_before_start(&data, envp);
		if (set_main())
			return (-1);
		prompt_while(data, &list, &parse, envp);
	}
	return (0);
}
