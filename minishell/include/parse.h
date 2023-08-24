/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youyoon <youyoon@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/16 15:39:09 by youyoon           #+#    #+#             */
/*   Updated: 2023/08/23 17:01:25 by youyoon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSE_H
# define PARSE_H

# define SUCCESS 	1
# define ERROR 		-1
# define STDERR		2
# define SYNTAX_ERROR	"Syntax error: near unexpected token!"
# define MALLOC_ERROR	"Malloc error: Memory malloc fail!"

# include "minishell.h"

/* src/parse/parse.c */
void				parser(char *input, char **envp);
void				put_buff_to_cmd(t_parse *parse);
int					parse_char(t_double_list *list, t_parse *parse, char *input, int *i);

/* src/utils/parse/utils_parse.c */
/* init and free struct */
t_double_list		*init_list();
t_parse				*init_parse(int token_cnt, int input_len, char **envp);
int					check_redir(char input, char input_next);
void				set_pipe_type(t_double_list *list);
void				set_list_idx(t_double_list *list);

/* src/utils/parse/utils_parse_env.c */
char				**set_env(char **envp);
char				*find_env(char *s, char **env);

/* src/utils/parse/utils_parse_list.c */
t_node				*make_node(t_parse *parse);
int					add_node(t_double_list *list, t_parse *parse);
void				ms_listadd_back(t_double_list *list, t_node *new_node);
void				ms_listadd_back_redir(t_double_list *list, t_node *new_node);

/* src/parse/parse_error.c */
void				parse_error(t_double_list *list, t_parse *parse, char *error_msg);

/* src/parse/parse_free.c */
void				free_parse(t_parse *parse);
void				free_list(t_double_list *list);
#endif