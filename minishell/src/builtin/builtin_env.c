
#include "../../include/minishell.h"

void	builtin_env(t_data *data)
{
	int	i;

	i = 0;
	while (g_envp[i])
	{
		ft_putendl_fd(g_envp[i], data->output_fd);
		i++;
	}
	data->exit_status = 0;
}
