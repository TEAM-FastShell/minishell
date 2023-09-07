#include "../../include/minishell.h"

void	builtin_pwd(void)
{
	char	*pwd;

	pwd = getcwd(NULL, 2048);
	printf("%s\n", pwd);
	free(pwd);
	pwd = NULL;
	g_exit_status = 0;
}
