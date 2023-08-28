#include "minishell.h"

void	builtin_env(t_data *data, t_node *node)
{
	int	i;

	i = 0;
	while (data->envp)
	{
		ft_putendl_fd(data->envp[i], data->output_fd);
		i++;
	}
	g_exit_status = 0;
}
