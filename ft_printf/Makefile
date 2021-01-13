# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jtanaka <jtanaka@student.42tokyo.jp>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/11/07 22:12:52 by jtanaka           #+#    #+#              #
#    Updated: 2020/12/21 06:42:57 by jtanaka          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS = ft_printf.c \
	   write_char_string.c \
	   write_integer.c \
	   write_percent.c \
	   parsers.c \
	   fmt_utils.c \
	   fmt_utils2.c \
	   utils.c
CC = gcc
CFLAGS = -Wall -Wextra -Werror
NAME = libftprintf.a
OBJS = $(SRCS:.c=.o)
LIBFT_MAKE = $(MAKE) -C ./libft

all: $(NAME)

$(NAME): ${OBJS}
	${LIBFT_MAKE}
	cp libft/libft.a $(NAME)
	ar rcs $(NAME) $(OBJS)

bonus: $(NAME)

clean:
	${RM} ${OBJS}
	${LIBFT_MAKE} clean

fclean: clean
	${RM} ${NAME}
	${LIBFT_MAKE} fclean

re: fclean all

.PHONY: all clean fclean re bonus
