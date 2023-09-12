/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seokklee <seokklee@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/07 19:47:31 by seokklee          #+#    #+#             */
/*   Updated: 2023/09/12 15:18:31 by seokklee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"
#include "minishell.h"

int	g_exit_status;

static void	print_awesome_prompt(void)
{
	printf("\n");
	printf("\033[0;36m███████╗ █████╗ ███████╗████████╗    \
	███████╗██╗  ██╗███████╗██╗     ██╗\n");
	printf("██╔════╝██╔══██╗██╔════╝╚══██╔══╝    \
	██╔════╝██║  ██║██╔════╝██║     ██║\n");
	printf("█████╗  ███████║███████╗   ██║       \
	███████╗███████║█████╗  ██║     ██║\n");
	printf("██╔══╝  ██╔══██║╚════██║   ██║       \
	╚════██║██╔══██║██╔══╝  ██║     ██║\n");
	printf("██║     ██║  ██║███████║   ██║       \
	███████║██║  ██║███████╗███████╗███████╗\n");
	printf("╚═╝     ╚═╝  ╚═╝╚══════╝   ╚═╝       \
	╚══════╝╚═╝  ╚═╝╚══════╝╚══════╝╚══════╝....by seokklee, youyoon\n\n");
}

static int	set_main(void)
{
	struct termios	term;
	int				res;

	print_awesome_prompt();
	res = 0;
	res += tcgetattr(STDIN_FILENO, &term);
	term.c_lflag &= ~(ECHOCTL);
	res += tcsetattr(STDIN_FILENO, TCSANOW, &term);
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
				t_parse *parse)
{
	char	*input;

	while (1)
	{
		set_signal(signal_handler, SIG_IGN);
		input = readline("\033[0;36mFastShell \033[0;33m⚡ \033[0;37m");
		if (!input)
			print_prompt(&input);
		else if (*input == '\0')
			g_exit_status = 0;
		else
		{
			add_history(input);
			if (!is_whitespace(input))
			{
				parser(input, data, list, parse);
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

void foo()
{
	system("leaks minishell");
}

/* 최종 사용한 struct 모두 free 구현 필요 */
int	main(int argc, char *argv[], char *envp[])
{
	t_double_list	list;
	t_parse			parse;
	t_data			*data;

	// atexit(foo);
	if (argc && argv)
	{
		init_data_before_start(&data, envp);
		if (set_main())
			return (-1);
		prompt_while(data, &list, &parse);
		rl_clear_history();
		parse_error(&list, &parse, data, NULL);
	}
	return (0);
}
