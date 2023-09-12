/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seokklee <seokklee@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/16 15:39:09 by youyoon           #+#    #+#             */
/*   Updated: 2023/09/12 19:16:11 by seokklee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSE_H
# define PARSE_H

# define SUCCESS 	1
# define ERROR 		-1
# define STDERR		2
# define SYNTAX_ERROR	"fastshell: Syntax error: unexpected token!"
# define MALLOC_ERROR	"fastshell: Malloc error: Memory malloc fail!"
# define PARSE_TOO_MANY_ARG "fastshell: Too many arguments"

# include "minishell.h"

/* src/parse/parse.c */
void	parser(char *input_tmp, t_data *data, \
		t_double_list *list, t_parse *parse);
int		parse_char(t_double_list *list, t_parse *parse, char *input, int *i);

/* src/utils/parse/utils_parse.c */
/* init and free struct */
void	init_list(t_double_list *list);
void	init_parse(t_parse *parse, int token_cnt, t_data *data, int input_len);
int		check_redir(char input, char input_next);
char	**copy_env(char **env);
void	init_in_while_data(t_data *data, t_double_list *list);

/* src/utils/parse/utils_parse2.c */
int		count_word(char *str);
void	init_data_before_start(t_data **data, char **envp);
char	*get_envv(char *envp[], char *envv);
int		check_env_char(char c);
char	*change_to_env(t_parse *parse, char *input, int start, int end);
void	put_env_to_buff(t_parse *parse, char *env, size_t input_len);

/* src/utils/parse/utils_parse_list.c */
t_node	*make_node(t_parse *parse);
int		add_node(t_double_list *list, t_parse *parse);
void	ms_listadd_back(t_double_list *list, t_node *new_node);
void	ms_listadd_back_redir(t_double_list *list, t_node *new_node);

/* src/utils/parse/utils_list_parse2.c */
void	set_pipe_type(t_double_list *list);
void	set_list_idx(t_double_list *list);
void	change_env(t_node *node, t_parse *parse);

/* src/parse/parse_error.c */
void	parse_error(t_double_list *list, t_parse *parse, t_data *data, \
		char *error_msg);

/* src/parse/parse_free.c */
void	free_parse(t_parse *parse);
void	free_list(t_double_list *list);

/* utils.c */
void	put_buff_to_cmd(t_parse *parse);
#endif
