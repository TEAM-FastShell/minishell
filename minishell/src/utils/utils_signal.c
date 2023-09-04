
#include "../../include/minishell.h"
#include "../../include/parse.h"

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
