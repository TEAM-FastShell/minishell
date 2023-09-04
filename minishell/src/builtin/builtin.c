#include "../../include/minishell.h"

int	is_builtin(char **cmd_args);

void	exec_builtin(t_data *data, t_node *node)
{
	char	*cmd;
	int		len_cmd;

	cmd = node->cmd_args[0];
	len_cmd = ft_strlen(cmd);
	if (!ft_strncmp(cmd, "echo", len_cmd))
		builtin_echo(data, node);
	else if (!ft_strncmp(cmd, "cd", len_cmd))
		builtin_cd(data, node);
	else if (!ft_strncmp(cmd, "pwd", len_cmd))
		builtin_pwd(data);
	else if (!ft_strncmp(cmd, "export", len_cmd))
		builtin_export(data, node);
	else if (!ft_strncmp(cmd, "unset", len_cmd))
		builtin_unset(data, node);
	else if (!ft_strncmp(cmd, "env", len_cmd))
		builtin_env(data);
	else if (!ft_strncmp(cmd, "exit", len_cmd))
		builtin_exit(node);
}

int	is_builtin(char **cmd_args)
{
	char	*cmd;
	int		len_cmd;

	cmd = cmd_args[0];
	len_cmd = ft_strlen(cmd);
	if (!ft_strncmp(cmd, "echo", len_cmd) || !ft_strncmp(cmd, "cd", len_cmd)\
	|| !ft_strncmp(cmd, "pwd", len_cmd) || !ft_strncmp(cmd, "export", len_cmd)\
	|| !ft_strncmp(cmd, "unset", len_cmd) || !ft_strncmp(cmd, "env", len_cmd)\
	|| !ft_strncmp(cmd, "exit", len_cmd))
		return (1);
	return (0);
}
