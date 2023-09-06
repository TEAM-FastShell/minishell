#include "../../include/minishell.h"
#include "../../include/parse.h"

static void	exec_pipe(t_data *data, t_node *node);
static void	wait_child(t_data *data);
static void	exec_child(t_data *data, t_node *node);
static char	*get_cmd(t_data *data, char *cmd_uncertain);


static void	exec_cmd(t_data *data, t_node *node);
static void	exec_child(t_data *data, t_node *node);
static void	exec_parent(t_data *data, t_node *node);

void	execute(t_data *data)
{
	t_node	*cur;

	cur = data->list->head;
	while (cur != NULL)
	{
		if (cur->cmd_args[0])
		{
			if (cur->redir_type != NO_REDIR)
			{
				exec_redir(data, cur);
				cur = cur->next;
				continue ;
			}
			else if (cur->pipe_type != NO_PIPE)
				exec_pipe(data, cur);
			if (is_builtin(cur->cmd_args) && cur->pipe_type == NO_PIPE)
				exec_builtin(data, cur);
			else
				exec_cmd(data, cur);
		}
		cur = cur->next;
	}
	free_pipe_fd(data);
	free_list(data->list);
}

static void	exec_pipe(t_data *data, t_node *node)
{
	ft_pipe(data, node);
}

static void	exec_cmd(t_data *data, t_node *node)
{
	ft_fork(node);
	if (node->pid == 0)
		exec_child(data, node);
	else if (node->pid > 0)
		exec_parent(data, node);
}

static void	exec_child(t_data *data, t_node *node)
{
	char	*cmd;

	if (is_builtin(node->cmd_args))
	{
		exec_builtin(data, node);
		exit(g_exit_status);
	}
	connect_pipe(data, node);
	cmd = get_cmd(data, node->cmd_args[0]);
	if (!cmd)
	{
		error_str_code(node, CMD_NOT_FOUND, 127);
		exit(127);
	}
	if (execve(cmd, node->cmd_args, data->envp) < 0)
	{
		error_str_code(node, strerror(errno), 127);
		exit(127);
	}
}

static void	exec_parent(t_data *data, t_node *node)
{
	if (data->input_fd != STDIN_FILENO)
		ft_close(data->input_fd);
	if (data->output_fd != STDOUT_FILENO)
		ft_close(data->output_fd);
	data->input_fd = 0;
	data->output_fd = 1;
	if (node->pipe_type == NO_PIPE || node->pipe_type == R_PIPE)
	{
		wait_child(data);
		close_all_pipes(data);
	}
}

static void	wait_child(t_data *data)
{
	t_node	*cur;

	cur = data->list->head;
	while (cur->next != NULL)
	{
		waitpid(cur->pid, &g_exit_status, 0);
		cur = cur->next;
	}
	waitpid(data->list->tail->pid, &g_exit_status, 0);
	g_exit_status = WEXITSTATUS(g_exit_status);
}

static char	*get_cmd(t_data *data, char *cmd_uncertain)
{
	char	*tmp;
	char	*cmd;
	char	**path_tab;

	if (!cmd_uncertain)
		return (NULL);
	else if (cmd_uncertain[0] == '/')
		return (cmd_uncertain);
	path_tab = ft_split(get_envv_data(data->envp, "PATH"), ':');
	while (*path_tab)
	{
		tmp = ft_strjoin(*path_tab, "/");
		cmd = ft_strjoin(tmp, cmd_uncertain);
		free(tmp);
		if (access(cmd, X_OK) == 0)
			return (cmd);
		free(cmd);
		path_tab++;
	}
	if (path_tab)
		free_tab(path_tab);
	return (NULL);
}
