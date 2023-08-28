# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: youyoon <youyoon@student.42seoul.kr>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/08/16 16:13:42 by youyoon           #+#    #+#              #
#    Updated: 2023/08/28 12:58:36 by youyoon          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

CC = gcc
CFLAGS = -Wall -Wextra -Werror
LDFLAGS = -lreadline

SRCS = src/parse/parse_error.c\
	src/parse/parse.c\
	src/parse/parse_free.c\
	src/utils/parse/utils_parse.c\
	src/utils/parse/utils_parse_list.c\
	src/utils/parse/utils_parse_list2.c\
	src/utils/utils.c\
	src/utils/utils_signal.c\
	src/main.c

OBJS_DIR = objs
OBJS = $(addprefix $(OBJS_DIR)/, $(SRCS:.c=.o))

all : $(NAME)

$(OBJS_DIR)/%.o: %.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

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
