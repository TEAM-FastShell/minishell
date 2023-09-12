/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seokklee <seokklee@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/28 13:35:11 by seokklee          #+#    #+#             */
/*   Updated: 2023/09/12 18:09:05 by seokklee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <fcntl.h>
# include <limits.h>
# include <unistd.h>
# include <errno.h>
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <stdlib.h>
# include <unistd.h>
# include <errno.h>
# include <signal.h>
# include <sys/wait.h>
# include <sys/types.h>
# include <termios.h>

# include "../libft/libft.h"

/* GNL BUFFER_SIZE */
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1024
# endif

/* ERR STRING */
# define NO_FILE_DIR "No such file or directory"
# define HOME_NOT_SET "HOME not set"
# define TOO_MANY_ARG "too many arguments"
# define NUM_ARG_REQ "numeric argument required"
# define NON_VALID_ID "not a valid identifier"
# define CMD_NOT_FOUND "command not found"

extern int	g_exit_status;

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
	int		cmd_cnt;
}	t_double_list;

typedef struct s_data
{
	t_double_list	*list;
	char			**envp;
	int				**pipe_fd;
	int				input_fd;
	int				output_fd;
}	t_data;

typedef struct s_parse
{
	char			**cmd;
	char			*buff;
	char			**env;
	char			quote;
	int				c_idx;
	int				b_idx;
	int				token_cnt;
	t_pipe_type		pipe_type;
	t_redir_type	redir_type;
}	t_parse;

/* src/utils/utils.c */
int		is_whitespace(char *str);
int		check_pipe_error(t_parse *parse, t_double_list *list);
/* src/utils/utils_signal.c */
void	signal_handler(int signo);
void	set_signal(void *int_handler, void *quit_handler);
void	execute_sigquit_handler(int signo);
void	execute_sigint_handler(int signo);
void	heredoc_sigint_handler(int signo);

/* execute */
void	execute(t_data *data);
void	exec_cmd(t_data *data, t_node *node);
void	control_pipe(t_data *data, t_node *node);
void	connect_fd(t_data *data);
void	close_fd(t_data *data, t_node *node);
void	exec_redir(t_data *data, t_node *node);

/* builtin */
int		is_builtin(char **cmd_args);
void	exec_builtin(t_data *data, t_node *node);
void	builtin_cd(t_data *data, t_node *node);
void	builtin_echo(t_node *node);
void	builtin_env(t_data *data);
void	builtin_exit(t_node *node);
void	builtin_export(t_data *data, t_node *node);
void	exec_export(t_data *data, char *export);
void	builtin_pwd(void);
void	builtin_unset(t_data *data, t_node *node);
void	builtin_history(void);

/* error */
void	error_code(int code);
void	error_str_code(t_node *node, char *str, int code);
void	error_str_str_code(t_node *node, char *str, int code);

/* utils */
void	ft_pipe(t_data *data, t_node *node);
void	ft_fork(t_node *node);
void	ft_dup2(int new_fd, int origin_fd);
void	ft_close(int fd);
void	ft_wait(void);
void	double_list_clear(t_double_list *list);
void	free_tab(char **tab);
void	close_all_pipes(t_data *data);
char	*get_envv_data(char *envp[], char *envv);
void	free_pipe_fd(t_data *data);
void	pipe_with_redir(t_data *data, t_node *node);

/* gnl */
char	*get_next_line(int fd);
char	*ft_strjoin_gnl(char *s1, char *s2);
char	*ft_substr(char const *s, unsigned int start, size_t len);
char	*ft_strdup(const char *s1);
char	*ft_strchr(const char *s, int c);

#endif
