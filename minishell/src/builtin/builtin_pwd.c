#include "minishell.h"

void	builtin_pwd(t_data *data, t_node *node)
{
	char	*pwd;

	pwd = getcwd(NULL, 2048);
	ft_putendl_fd(pwd, data->output_fd);
	free(pwd);
	g_exit_status = 0;
}
