#include "minishell.h"

void	execute(t_list *list)
{
	t_node	*cur;
	int		idx_fd;

	cur = list->head;
	idx_fd = 0;
	while (cur != NULL)
	{
		if (cur->cmd_args[0])
		{
			if (cur->redir_type != NO_REDIR && cur->pipe_type == NO_PIPE)
			{
				exec_redir(cur->cmd_args);
				break ;
			}
			if (is_builtin(cur->cmd_args) && cur->pipe_type == NO_PIPE)
				exec_builtin(cur->cmd_args);
			else
				exec_pipe(cur, idx_fd++);
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

void	exec_pipe(t_node *node, int idx_fd)
{
	if (node->pipe_type == NO_PIPE)
		exec_cmd(node->cmd_args);
	else
		ft_pipe(node, idx_fd);
	ft_fork(node);
	if (node->pid == 0)
		exec_cmd(node->cmd_args);
	else if (node->pid > 0)
	/* pipe 재 구현 해보기 */
}
