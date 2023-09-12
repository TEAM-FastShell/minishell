# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: seokklee <seokklee@student.42seoul.kr>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/08/16 16:13:42 by youyoon           #+#    #+#              #
#    Updated: 2023/09/12 18:23:13 by seokklee         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

CC = cc
CFLAGS = -Wall -Wextra -Werror
LDFLAGS = -I/opt/homebrew/opt/readline/include -lreadline -L /opt/homebrew/opt/readline/lib
AR = ar
RM = rm
RMFLAGS = -rf
INCS = -I $(MINI_HDR) -I $(LIBFT_HDR)
NAME = minishell

MINI_HDR = ./include/

LIBFT = $(LIBFT_DIR)libft.a
LIBFT_DIR = ./libft/
LIBFT_HDR = $(LIBFT_DIR)include/

SRCS_BUILTIN = builtin_cd.c\
	builtin_echo.c\
	builtin_env.c\
	builtin_exit.c\
	builtin_export.c\
	builtin_history.c\
	builtin_pwd.c\
	builtin_unset.c\
	builtin.c\

SRCS_ERROR = error.c\

SRCS_EXECUTE = execute.c\
	pipe.c\
	redirection.c\
	connect_fd.c\
	close_fd.c\

SRCS_PARSE = parse.c\
	parse_error.c\
	parse_free.c\

SRCS_UTILS = ft_function.c\
	get_next_line.c\
	get_next_line_utils.c\
	utils_clear.c\
	utils_parse_list.c\
	utils_parse_list2.c\
	utils_parse.c\
	utils_parse2.c\
	utils_signal.c\
	utils.c\

SRC = main.c\

SRC_BUILTIN_DIR = src/builtin/
SRC_ERROR_DIR = src/error/
SRC_EXECUTE_DIR = src/execute/
SRC_PARSE_DIR = src/parse/
SRC_UTILS_DIR = src/utils/
SRC_DIR = src/

SRCS = $(addprefix $(SRC_DIR), $(SRC))\
	$(addprefix $(SRC_BUILTIN_DIR), $(SRCS_BUILTIN))\
	$(addprefix $(SRC_ERROR_DIR), $(SRCS_ERROR))\
	$(addprefix $(SRC_EXECUTE_DIR), $(SRCS_EXECUTE))\
	$(addprefix $(SRC_PARSE_DIR), $(SRCS_PARSE))\
	$(addprefix $(SRC_UTILS_DIR), $(SRCS_UTILS))\

OBJ = $(SRCS:.c=.o)
OBJS_DIR = obj/
OBJS = $(addprefix $(OBJS_DIR), $(OBJ))

all : $(NAME)

$(NAME) : $(LIBFT) $(OBJS_DIR) $(OBJS)
	$(CC) $(CFLAGS) $(LIBFT) $(INCS) $(OBJS) -o $@ $(LDFLAGS)

$(OBJS_DIR):
	mkdir $(OBJS_DIR)
	mkdir $(OBJS_DIR)$(SRC_DIR)
	mkdir $(OBJS_DIR)$(SRC_BUILTIN_DIR)
	mkdir $(OBJS_DIR)$(SRC_ERROR_DIR)
	mkdir $(OBJS_DIR)$(SRC_EXECUTE_DIR)
	mkdir $(OBJS_DIR)$(SRC_PARSE_DIR)
	mkdir $(OBJS_DIR)$(SRC_UTILS_DIR)

$(OBJS_DIR)%.o: %.c
	$(CC) $(CFLAGS) $(INCS) -I/opt/homebrew/opt/readline/include/ -c $< -o $@

$(LIBFT):
	make -C $(LIBFT_DIR)

clean:
	make -C $(LIBFT_DIR) clean
	$(RM) $(RMFLAGS) $(OBJS_DIR)

fclean: clean
	make -C $(LIBFT_DIR) fclean
	$(RM) $(RMFLAGS) $(NAME)

re :
	make fclean
	make all

.PHONY : all clean fclean re
