
#include "../../include/minishell.h"

void	builtin_pwd(t_data *data)
{
	char	*pwd;

	pwd = getcwd(NULL, 2048);
	ft_putendl_fd(pwd, data->output_fd);
	free(pwd);
	pwd = NULL;
	data->exit_status = 0;
}
