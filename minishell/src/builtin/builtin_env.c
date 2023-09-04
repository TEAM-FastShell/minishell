#include "../../include/minishell.h"

void	builtin_env(t_data *data)
{
	int	i;

	i = 0;
	while (data->envp[i])
	{
		ft_putendl_fd(data->envp[i], data->output_fd);
		i++;
	}
	g_exit_status = 0;
}
