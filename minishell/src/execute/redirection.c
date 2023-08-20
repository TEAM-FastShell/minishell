#include "minishell.h"

void	exec_redir(t_data *data, t_node *node)
{
	int	i;

	if ((node->redir_type == R_REDIR || node->redir_type == H_REDIR)
	&& data->input_fd != STDIN_FILENO)
		ft_close(data->input_fd);
	if ((node->redir_type == W_REDIR || node->redir_type == A_REDIR)
	&& data->output_fd != STDOUT_FILENO)
		ft_close(data->output_fd);
	ft_open_redir(data, node);
	if (node->redir_type == H_REDIR)
		get_heredoc(data, node);
	if (data->input_fd < 0 || data->output_fd < 0)
		/*error open*/
}

void	ft_open_redir(t_data *data, t_node *node)
{
	t_redir_type	type;
	char			*file_name;

	type = node->redir_type;
	file_name = node->cmd_args[0];
	if (type == R_REDIR)
		data->input_fd = open(file_name, O_RDONLY);
	else if (type == W_REDIR)
		data->output_fd = open(file_name, O_CREAT | O_TRUNC | O_RDWR, 0644);
	else if (type == A_REDIR)
		data->output_fd = open(file_name, O_CREAT | O_APPEND | O_RDWR, 0644);
	else if (type == H_REDIR)
	{
		while (!access(file_name, F_OK))
			file_name[5]++;
		data->input_fd = open(file_name, O_CREAT | O_TRUNC | O_RDWR, 0644);
		node->cmd_args[0] = file_name;
	}
}

void	get_heredoc(t_data *data, t_node *node)
{
	char	*line;

	write(1, "> ", 2);
	line = get_next_line(0);
	while (line)
	{
		if (!ft_strncmp(line, node->cmd_args[1], ft_strlen(line)))
			break ;
		write(data->input_fd, line, ft_strlen(line));
		free(line);
		write(1, "> ", 2);
		line = get_next_line(0);
	}
	free(line);
	ft_close(data->input_fd);
	data->input_fd = open(node->cmd_args[0], O_RDONLY);
	unlink(node->cmd_args[0]);
}
