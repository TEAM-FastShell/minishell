#include "../../include/minishell.h"

static void	ft_open_redir(t_data *data, t_node *node);
static void	get_heredoc(t_data *data, t_node *node, char *file_name);

void	exec_redir(t_data *data, t_node *node)
{
	if ((node->redir_type == R_REDIR || node->redir_type == H_REDIR)
		&& data->input_fd != STDIN_FILENO)
		ft_close(data->input_fd);
	if ((node->redir_type == W_REDIR || node->redir_type == A_REDIR)
		&& data->output_fd != STDOUT_FILENO)
		ft_close(data->output_fd);
	ft_open_redir(data, node);
	if (data->input_fd < 0 || data->output_fd < 0)
		ft_putendl_fd(strerror(errno), STDERR_FILENO);
}

static void	ft_open_redir(t_data *data, t_node *node)
{
	char			*file_name;

	file_name = node->cmd_args[0];
	if (node->redir_type == R_REDIR)
		data->input_fd = open(file_name, O_RDONLY);
	else if (node->redir_type == W_REDIR)
		data->output_fd = open(file_name, O_CREAT | O_TRUNC | O_RDWR, 0644);
	else if (node->redir_type == A_REDIR)
		data->output_fd = open(file_name, O_CREAT | O_APPEND | O_RDWR, 0644);
	else if (node->redir_type == H_REDIR)
	{
		file_name = ft_strdup("here_doc!");
		while (!access(file_name, F_OK))
			file_name[8]++;
		data->input_fd = open(file_name, O_CREAT | O_TRUNC | O_RDWR, 0644);
		get_heredoc(data, node, file_name);
	}
}

static void	get_heredoc(t_data *data, t_node *node, char *file_name)
{
	char	*line;

	set_signal(heredoc_sigint_handler, SIG_IGN);
	// write(1, "> ", 2);
	// line = get_next_line(0);
	line = readline("> ");
	while (1)
	{
		if (g_exit_status)
			break ;
		if (!ft_strncmp(line, node->cmd_args[0], ft_strlen(line) - 1))
			break ;
		write(data->input_fd, line, ft_strlen(line));
		free(line);
		write(1, "> ", 2);
		if (g_exit_status)
			break ;
		//line = get_next_line(0);
		
	}
	free(line);
	ft_close(data->input_fd);
	data->input_fd = open(file_name, O_RDONLY);
	unlink(file_name);
}
