# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: youyoon <youyoon@student.42seoul.kr>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/08/16 16:13:42 by youyoon           #+#    #+#              #
#    Updated: 2023/08/29 19:10:32 by youyoon          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

CC = gcc
CFLAGS = -Wall -Wextra -Werror #-fsanitize=address -g2
LDFLAGS = -I/opt/homebrew/opt/readline/include -lreadline #-L /opt/homebrew/opt/readline/lib

SRCS = src/parse/parse_error.c\
	src/parse/parse.c\
	src/parse/parse_free.c\
	src/utils/parse/utils_parse.c\
	src/utils/parse/utils_parse2.c\
	src/utils/parse/utils_parse_list.c\
	src/utils/parse/utils_parse_list2.c\
	src/utils/utils.c\
	src/utils/utils_signal.c\
	src/utils/ft_function.c\
	src/utils/get_next_line_utils.c\
	src/utils/get_next_line.c\
	src/utils/utils_clear.c\
	src/main.c\
	src/builtin/builtin_cd.c\
	src/builtin/builtin_echo.c\
	src/builtin/builtin_env.c\
	src/builtin/builtin_exit.c\
	src/builtin/builtin_export.c\
	src/builtin/builtin_pwd.c\
	src/builtin/builtin_unset.c\
	src/builtin/builtin.c\
	src/error/error.c\
	src/execute/execute.c\
	src/execute/pipe.c\
	src/execute/redirection.c\

OBJS_DIR = objs
OBJS = $(addprefix $(OBJS_DIR)/, $(SRCS:.c=.o))

all : $(NAME)

$(OBJS_DIR)/%.o: %.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -I/opt/homebrew/opt/readline/include/ -c $< -o $@

$(NAME) : $(OBJS)
	make -C ./libft
	$(CC) $(CFLAGS) $(OBJS) -o $@ libft/libft.a $(LDFLAGS)

clean:
	make clean -C ./libft
	rm -rf $(OBJS_DIR)

fclean: clean
	make fclean -C ./libft
	rm -rf $(NAME)

re : fclean all

.PHONY : all clean fclean re
