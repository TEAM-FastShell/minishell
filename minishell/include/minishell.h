#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <stdlib.h>
# include <unistd.h>
# include <errno.h>
# include <signal.h>
# include <sys/wait.h>
# include "../libft/libft.h"

# define STDIN 			0
# define STDOUT 		1
# define STDERR 		2

typedef enum e_pipe_type
{
	NO_PIPE = 0,
	W_PIPE,
	R_PIPE,
	RW_PIPE,
}	t_pipe_type;

/*
	W_REDIR : >
	R_REDIR : <
	A_REDIR : >>
	H_REDIR : <<
*/

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
	struct s_node			*prev;
	struct s_node			*next;
	char					**cmd_args;
	t_pipe_type				pipe_type;
	t_redir_type			redir_type;
	pid_t					pid;
	int						idx;
}	t_node;

typedef struct s_double_list
{
	t_node	*head;
	t_node	*tail;
	int		cnt;
	//int		redir_cnt;
	int		cmd_cnt;
}	t_double_list;

typedef struct s_data
{
	t_list	*list;
	char	**envp;
	int		*pipe_fd[2];
	int		status;
}	t_data;

typedef struct s_parse
{
	char			**cmd;
	char			*buff;
	char			quote;
	int				c_idx;
	int				b_idx;
	t_pipe_type		pipe_type;
	t_redir_type	redir_type;
}	t_parse;

/* src/utils/utils.c */
int		is_whitespace(char *str);

/* src/utils/utils_signal.c */
void	set_signal(void);
void	signal_handler(int signo);

#endif
