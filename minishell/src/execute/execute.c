#include "minishell.h"

void	execute(t_data *data)
{
	t_node	*cur;
	int		idx_fd;

	cur = data->list->head;
	while (cur != NULL)
	{
		if (cur->cmd_args[0])
		{
			if (cur->redir_type != NO_REDIR && cur->pipe_type == NO_PIPE)
			{
				exec_redir(data, cur);
				// exec_cmd(data, cur);
				break ;
			}
			if (is_builtin(cur->cmd_args) && cur->pipe_type == NO_PIPE)
				exec_builtin(cur->cmd_args);
			else
				exec_pipe(data, cur);
		}
		cur = cur->next;
	}
	/* list clear */
}

int	is_builtin(char **cmd_args)
{
	char	*cmd;
	int		len_cmd;

	cmd = cmd_args[0];
	len_cmd = ft_strlen(cmd);
	if (!ft_strncmp(cmd, "echo", len_cmd) || !ft_strncmp(cmd, "cd", len_cmd)
	|| !ft_strncmp(cmd, "pwd", len_cmd) || !ft_strncmp(cmd, "export", len_cmd)
	|| !ft_strncmp(cmd, "unset", len_cmd) || !ft_strncmp(cmd, "env", len_cmd)
	|| !ft_strncmp(cmd, "exit", len_cmd))
		return (1);
	return (0);
}

void	exec_builtin(char **cmd_args)
{
	char	*cmd;
	int		len_cmd;

	cmd = cmd_args[0];
	len_cmd = ft_strlen(cmd); /* len 구하지 않으면 이상한 cmd 실행 가능 */
	if (!ft_strncmp(cmd, "echo", len_cmd))
		builtin_echo(cmd_args);
	else if (!ft_strncmp(cmd, "cd", len_cmd))
		builtin_cd(cmd_args);
	else if (!ft_strncmp(cmd, "pwd", len_cmd))
		builtin_pwd(cmd_args);
	else if (!ft_strncmp(cmd, "export", len_cmd))
		builtin_export(cmd_args);
	else if (!ft_strncmp(cmd, "unset", len_cmd))
		builtin_unset(cmd_args);
	else if (!ft_strncmp(cmd, "env", len_cmd))
		builtin_env(cmd_args);
	else if (!ft_strncmp(cmd, "exit", len_cmd))
		builtin_exit(cmd_args);
	else
		return (0);
	return (1);
}

void	exec_pipe(t_data *data, t_node *node)
{
	if (node->pipe_type != NO_PIPE)
		ft_pipe(data, node);
	if (node->redir_type != NO_REDIR)
		exec_redir(data, node);
	ft_fork(node);
	if (node->pid == 0)
		exec_cmd(data, node);
	else if (node->pid > 0)
	{
		/*리다 복구 혹은 포크 하고 리다*/
		if (node->pipe_type == W_PIPE || NO_PIPE)
		{
			close_pipes(data);
			wait_child(data);
		}
	}
}

void	wait_child(t_data *data)
{
	int	i;

	i = 0;
	while (i++ < data->list->cnt)
		ft_wait();
	waitpid(data->list->tail->prev->pid, &data->status, 0);
}

void	exec_cmd(t_data *data, t_node *node)
{
	char	*cmd;

	connect_pipe(data, node);
	cmd = get_cmd(data->path_tab, node->cmd_args[0]);
	if (!cmd)
		/*error cmd not found*/
	if (execve(cmd, node->cmd_args, data->envp) < 0)
		/*error execve*/
}

void	connect_pipe(t_data *data, t_node *node) /*파이프 안에 리다이렉션 처리 echo hi > a.txt | wc*/
{
	if (node->pipe_type == NO_PIPE)
		return ;
	else if (node->pipe_type == W_PIPE)
	{
		ft_dup2(data->pipe_fd[node->idx][1], 1);
		ft_close(data->pipe_fd[node->idx][0]);
	}
	else if (node->pipe_type == RW_PIPE)
	{
		ft_dup2(data->pipe_fd[node->idx - 1][0], 0);
		ft_dup2(data->pipe_fd[node->idx][1], 1);
		ft_close(data->pipe_fd[node->idx - 1][1]);
		ft_close(data->pipe_fd[node->idx][0]);
		close_pipes(data);
	}
	else
	{
		ft_dup2(data->pipe_fd[node->idx - 1][0], 0);
		ft_close(data->pipe_fd[node->idx - 1][1]);
		ft_close(data->pipe_fd[node->idx][0]);
		ft_close(data->pipe_fd[node->idx][1]);
		close_pipes(data);
	}
}

char	*get_cmd(char **path_tab, char *cmd_uncertain)
{
	char	*tmp;
	char	*cmd;

	if (!cmd_uncertain)
		return (NULL);
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
	return (NULL);
}
