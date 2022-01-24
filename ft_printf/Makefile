# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: amarchal <amarchal@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/09/23 12:28:09 by amarchal          #+#    #+#              #
#    Updated: 2021/11/19 14:02:29 by amarchal         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS =	ft_printf.c			\
		ft_putnbr_base.c	\
		ft_putstr.c			\
		ft_putchar.c		\
		ft_strlen.c

OBJS = $(SRCS:.c=.o)
HDRS = ft_printf.h
CC = gcc
CFLAGS = -Wall -Wextra -Werror
NAME = libftprintf.a

%.o : %.c $(HDRS)
	$(CC) $(CFLAGS) -c $< -o $@ 

all:	$(NAME)

$(NAME): $(OBJS)
		ar rcs $(NAME) $(OBJS)
		
clean:
		rm -rf $(OBJS)

fclean:	clean
		rm -rf $(NAME)

re:		fclean all

.PHONY:	all clean fclean re 
