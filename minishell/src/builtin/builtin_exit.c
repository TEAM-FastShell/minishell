#include "minishell.h"

static int	is_num_str(char *n);

void	builtin_exit(t_data *data, t_node *node)
{
	int	i;

	if (node->pipe_type == R_PIPE || node->pipe_type == RW_PIPE)
		return ;
	i = 0;
	while (node->cmd_args[i])
		i++;
	if (i == 1)
		ft_putendl_fd("exit", STDOUT_FILENO);
	else if (i == 2 && is_num_str(node->cmd_args[1]))
		g_exit_status = ft_atoi(node->cmd_args[1]);
	else if (i > 2 && is_num_str(node->cmd_args[1]))
	{
		error_str_code(node, TOO_MANY_ARG, 1);
		return ;
	}
	else
		error_str_str_code(node, NUM_ARG_REQ, 255);
	exit(g_exit_status);
}/*long long*/

static int	is_num_str(char *n)
{
	int	i;

	i = 0;
	while (n[i])
	{
		if (!ft_isdigit(n[i]))
			return (0);
	}
	return (1);
}
