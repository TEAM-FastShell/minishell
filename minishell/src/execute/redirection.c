#include "minishell.h"

void	exec_redir(t_data *data, t_node *node) /* 갯수*/
{
	int	i;

	ft_open_redir(data, node->cmd_args[1], node->redir_type);
	i = 1;
	while (node->cmd_args[i])
	{
		node->cmd_args[i] = node->cmd_args[i + 1];
		i++;
	}
}

void	ft_open_redir(t_data *data, char *file_name, t_redir_type type)
{
	char	*tmp;

	if (type == R_REDIR)
		data->input_fd = open(file_name, O_RDONLY);
	else if (type == W_REDIR)
		data->output_fd = open(file_name, O_CREAT | O_TRUNC | O_RDWR, 0644);
	else if (type == A_REDIR)
		data->output_fd = open(file_name, O_CREAT | O_APPEND | O_RDWR, 0644);
	else if (type == H_REDIR)
	{
		tmp = ft_strdup("hd_rd!");
		while (!access(tmp, F_OK))
			tmp[5]++;
		data->input_fd = open(tmp, O_CREAT | O_TRUNC | O_RDWR, 0644);
	}
	if (data->input_fd < 0 || data->output_fd < 0)
		/*error open*/
}
