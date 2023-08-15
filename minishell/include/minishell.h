#ifndef MINISHELL_H
# define MINISHELL_H

typedef enum e_pipe_type
{
    NO_PIPE = 0,
    W_PIPE,
    R_PIPE,
    RW_PIPE,
}   t_pipe_type;

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
}   t_redir_type;

typedef struct s_node
{
    t_node          *prev;
    t_node          *next;
    char            **cmd_args;
    t_pipe_type     pipe_type;
    t_redir_type    redir_type;
}	t_node;

typedef struct s_list
{
    t_node  *head;
    t_node  *tail;
    int     cnt;
}   t_list;

#endif
