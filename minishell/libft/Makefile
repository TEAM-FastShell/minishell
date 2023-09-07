# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: seokklee <seokklee@student.42seoul.kr>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/11/11 16:23:11 by youyoon           #+#    #+#              #
#    Updated: 2023/09/07 18:34:32 by seokklee         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a

CC = cc
CFLAG = -Wall -Wextra -Werror

RM = rm -f

AR = ar
ARFLAG = crs

INCLUDES = ./libft.h

SRCS_1 = ft_bzero.c		\
		ft_isalnum.c	\
		ft_isalpha.c	\
		ft_isascii.c	\
		ft_isdigit.c	\
		ft_isprint.c	\
		ft_memcpy.c		\
		ft_memmove.c	\
		ft_memset.c		\
		ft_strlcpy.c	\
		ft_strlen.c		\
		ft_strlcat.c	\
		ft_strncmp.c	\
		ft_atoi.c		\
		ft_toupper.c	\
		ft_tolower.c	\
		ft_strchr.c		\
		ft_strrchr.c	\
		ft_strnstr.c	\
		ft_memcmp.c		\
		ft_memchr.c		\
		ft_calloc.c		\
		ft_strdup.c		\
		ft_substr.c		\
		ft_strjoin.c	\
		ft_strtrim.c	\
		ft_split.c		\
		ft_itoa.c		\
		ft_strmapi.c	\
		ft_striteri.c	\
		ft_putchar_fd.c	\
		ft_putstr_fd.c	\
		ft_putendl_fd.c	\
		ft_putnbr_fd.c	\
		ft_lstnew.c		\

SRCS_BONUS = ft_lstnew.c		\
			ft_lstadd_front.c	\
			ft_lstsize.c		\
			ft_lstlast.c		\
			ft_lstadd_back.c	\
			ft_lstdelone.c		\
			ft_lstclear.c		\
			ft_lstiter.c		\
			ft_lstmap.c

SRCS = $(SRCS_1)
SRCS_BNS = $(SRCS_BONUS)

OBJS	= $(SRCS:.c=.o)
OBJS_BONUS = $(SRCS_BNS:.c=.o)

all : $(NAME)

%.o : %.c
	$(CC) $(CFLAG) -c $< -o $@

clean :
	$(RM) $(RMFLAG) $(OBJS) $(OBJS_BONUS)

fclean : clean
	$(RM) $(RMFLAG) $(NAME)

re : fclean all

$(NAME) : $(OBJS)
		$(AR) $(ARFLAG) $@ $^

bonus : $(OBJS) $(OBJS_BONUS)
	$(AR) $(ARFLAGS) $(NAME) $^

.PHONY : all clean fclean re
