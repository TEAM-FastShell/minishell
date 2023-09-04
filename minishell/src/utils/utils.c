#include "../../include/minishell.h"
#include "../../include/parse.h"

int	is_whitespace(char *str)
{
	int	i;
	int	space;

	i = 0;
	space = 0;
	if ((int) ft_strlen(str) == 0)
		return (1);
	while (str[i])
	{
		if (str[i] == '\r' || str[i] == '\v' || \
				str[i] == '\t' || str[i] == '\f')
			return (1);
		else if (str[i] == ' ')
			space++;
		i++;
	}
	if ((int) ft_strlen(str) == space)
		return (1);
	return (0);
}

char	*get_envv_data(char *envp[], char *envv)
{
	while (*envp)
	{
		if (!ft_strncmp(*envp, envv, ft_strlen(envv)))
			return (*envp + ft_strlen(envv) + 1);
		envp++;
	}
	return ("");
}

void	free_pipe_fd(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->list->cmd_cnt - 1)
	{
		free(data->pipe_fd[i]);
		data->pipe_fd[i] = NULL;
		i++;
	}
	free(data->pipe_fd);
	data->pipe_fd = NULL;
}
