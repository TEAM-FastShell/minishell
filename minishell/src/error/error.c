#include "../../include/minishell.h"

void	error_code(int code)
{
	g_exit_status = code;
	ft_putendl_fd("exit", STDERR_FILENO);
}

void	error_str_code(t_node *node, char *str, int code)
{
	g_exit_status = code;
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	ft_putstr_fd(node->cmd_args[0], STDERR_FILENO);
	ft_putstr_fd(": ", STDERR_FILENO);
	ft_putendl_fd(str, STDERR_FILENO);
}

void	error_str_str_code(t_node *node, char *str, int code)
{
	g_exit_status = code;
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	ft_putstr_fd(node->cmd_args[0], STDERR_FILENO);
	ft_putstr_fd(": ", STDERR_FILENO);
	ft_putstr_fd(node->cmd_args[1], STDERR_FILENO);
	ft_putstr_fd(": ", STDERR_FILENO);
	ft_putendl_fd(str, STDERR_FILENO);
}
