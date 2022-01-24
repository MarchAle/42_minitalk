/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarchal <amarchal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/19 11:29:23 by amarchal          #+#    #+#             */
/*   Updated: 2022/01/24 18:32:03 by amarchal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include "./ft_printf/ft_printf.h"
#include "./libft/libft.h"
#include "minitalk.h"

void	print_msg(int sig)
{
	static char	*temp_msg = {0};
	static int	bit = 0;
	static int	nb_bit = 0;
	int			current_size;
	char		*message;
	
	if (sig == SIGUSR2)
		bit += 1 << nb_bit;
	nb_bit++;
	if (nb_bit == 8)
	{
		if (bit == '\0')
		{
			ft_printf("%s\n", temp_msg);
			temp_msg[0] = '\0';
		}
		else
		{
			if (temp_msg)
				current_size = ft_strlen(temp_msg);
			else
				current_size = 0;
			message = ft_calloc(1, current_size + 1 + 1);
			if (temp_msg)
				ft_strlcpy(message, temp_msg, current_size + 1);
			message[current_size] = bit;
			if (temp_msg)
			{
				ft_strlcat(temp_msg, message, current_size + 1);
				free(temp_msg);
			}
			temp_msg = ft_strdup(message);
			free(message);
		}
		nb_bit = 0;
		bit = 0;
	}
}

void	kill_process(int sig)
{
	ft_printf("\nServer shut down\n");
	kill(getpid(), 9);
	(void)sig;
}

int	main(void)
{
	struct sigaction	sa;
	
	sa.sa_handler = &print_msg;
	sa.sa_flags = SA_RESTART;
	ft_printf("pid = %d\n", getpid());
	sigaction(SIGUSR1, &sa, NULL);
	sigaction(SIGUSR2, &sa, NULL);
	signal(SIGTERM, kill_process);
	signal(SIGINT, kill_process);
	while (1)
	{
		pause();
	}
}
