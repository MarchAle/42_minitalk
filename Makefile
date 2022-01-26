# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: amarchal <amarchal@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/09/23 12:28:09 by amarchal          #+#    #+#              #
#    Updated: 2022/01/26 15:45:18 by amarchal         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRV_NAME = server

CLIENT_NAME = client

LIB = ./libft/libft.a

FT_PRINTF = ./ft_printf/libftprintf.a

SRV_SRCS =	./server.c

CLIENT_SRCS =	./client.c

HDRS = 	./minitalk.h

SRV_OBJS = $(SRV_SRCS:.c=.o)

CLIENT_OBJS = $(CLIENT_SRCS:.c=.o)

CC = gcc

CFLAGS = -Wall -Wextra -Werror

%.o : %.c $(HDRS)
	$(CC) $(CFLAGS) -c $< -o $@
	
all: libft ft_printf $(SRV_NAME) $(CLIENT_NAME)

libft:
	make -C ./libft

ft_printf:
	make -C ./ft_printf

$(CLIENT_NAME): $(CLIENT_OBJS) $(FT_PRINTF) $(LIB)
		$(CC) $(CLIENT_OBJS) $(FT_PRINTF) $(LIB) -o $(CLIENT_NAME)

$(SRV_NAME): $(SRV_OBJS) $(FT_PRINTF) $(LIB)
		$(CC) $(SRV_OBJS) $(FT_PRINTF) $(LIB) -o $(SRV_NAME)

clean:
		rm -rf $(SRV_OBJS)
		rm -rf $(CLIENT_OBJS)
		make clean -C ./libft
		make clean -C ./ft_printf

fclean:	clean
		rm -rf $(SRV_NAME)
		rm -rf $(CLIENT_NAME)
		rm -rf $(LIB)
		rm -rf $(FT_PRINTF)

re:		fclean all

.PHONY:	all clean fclean re ft_printf libft
