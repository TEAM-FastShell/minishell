#include "minishell.h"

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
