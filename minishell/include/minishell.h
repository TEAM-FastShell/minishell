#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/libft.h"
# include <fcntl.h>
# include <limits.h>
# include <unistd.h>
# include <errno.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1024
# endif

# define NO_FILE_DIR "No such file or directory"
# define HOME_NOT_SET "HOME not set"
# define TOO_MANY_ARG "too many arguments"
# define NUM_ARG_REQ "numeric argument required"
# define NON_VALID_ID "not a valid identifier"
# define CMD_NOT_FOUND "command not found"

int	g_exit_status;

typedef enum e_pipe_type
{
	NO_PIPE = 0,
	W_PIPE,
	R_PIPE,
	RW_PIPE,
}	t_pipe_type;

typedef enum e_redir_type
{
	NO_REDIR = 0,
	W_REDIR,
	R_REDIR,
	A_REDIR,
	H_REDIR,
}	t_redir_type;

typedef struct s_node
{
	t_node			*prev;
	t_node			*next;
	char			**cmd_args; /* cmd [options] or re_file(hd_rd!) [lim]*/
	t_pipe_type		pipe_type;
	t_redir_type	redir_type;
	pid_t			pid;
	int				idx; /* cmd 부터 idx++ */
}	t_node;

typedef struct s_double_list
{
	t_node	*head;
	t_node	*tail;
	int		cnt;
	int		cmd_cnt;
}	t_double_list;

typedef struct s_data
{
	t_double_list	*list;
	char			**envp;
	char			**path_tab;
	int				*pipe_fd[2];
	int				input_fd;
	int				output_fd;
}	t_data;

#endif
