#include "../../include/minishell.h"

void	builtin_echo(t_node *node)
{
	int	new_line;
	int	i;

	new_line = 1;
	i = 1;
	if (node->cmd_args[i] == NULL)
	{
		printf("\n");
		return ;
	}
	if (!strncmp(node->cmd_args[i], "-n", ft_strlen(node->cmd_args[i])))
	{
		new_line = 0;
		i++;
	}
	while (node->cmd_args[i])
	{
		printf("%s", node->cmd_args[i]);
		if (node->cmd_args[i + 1] != NULL)
			printf(" ");
		i++;
	}
	if (new_line)
		printf("\n");
	g_exit_status = 0;
}
