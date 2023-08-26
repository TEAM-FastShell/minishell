#include "minishell.h"

void	ft_pipe(t_data *data, t_node *node)
{
	if (pipe(data->pipe_fd[node->idx]) < 0)
		ft_putendl_fd(strerror(errno), STDERR_FILENO);
}

void	ft_fork(t_node *node)
{
	node->pid = fork();
	if (node->pid < 0)
		ft_putendl_fd(strerror(errno), STDERR_FILENO);
}

void	ft_dup2(int	new_fd, int origin_fd)
{
	if (dup2(new_fd, origin_fd) < 0)
		ft_putendl_fd(strerror(errno), STDERR_FILENO);
}

void	close_all_pipes(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->list->cmd_cnt - 1)
	{
		ft_close(data->pipe_fd[i][0]);
		ft_close(data->pipe_fd[i][1]);
		i++;
	}
}

void	ft_close(int fd)
{
	if (close(fd) < 0)
		ft_putendl_fd(strerror(errno), STDERR_FILENO);
}

void	ft_wait(void)
{
	if (wait(NULL) < 0)
		ft_putendl_fd(strerror(errno), STDERR_FILENO);
}
