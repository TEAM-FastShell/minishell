
#include "../../../include/minishell.h"
#include "../../../include/parse.h"

int	count_word(char *str)
{
	int	cnt;

	cnt = 0;
	while (*str)
	{
		while (*str == ' ' || (9 <= *str && *str <= 13))
			str++;
		if (*str && !(*str == ' ' || (9 <= *str && *str <= 13)))
		{
			cnt++;
			while (*str && !(*str == ' ' || (9 <= *str && *str <= 13)))
				str++;
		}
	}
	return (cnt);
}

void	init_data_before_start(t_data **data, char **envp)
{
	*data = (t_data *) malloc(sizeof(t_data));
	if (!(*data))
		return (parse_error(NULL, NULL, NULL, MALLOC_ERROR));
	(*data)->list = NULL;
	(*data)->path_tab = NULL;
	(*data)->pipe_fd = NULL;
	(*data)->envp = copy_env(envp);
	if (!(*data)->envp)
		return (parse_error(NULL, NULL, (*data), MALLOC_ERROR));
}
