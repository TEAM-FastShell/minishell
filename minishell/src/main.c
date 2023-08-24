#include "../include/parse.h"
#include "../include/minishell.h"

int	main(int argc, char *argv[], char *envp[])
{
	char	*input;
	(void) argc;
	(void) argv;

	set_signal();
	while (1)
	{
		input = readline("Minishell> ");
		if (!(is_whitespace(input)))
			parser(input, envp);
		add_history(input);
		free(input);
		
	}
}
