/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarchal <amarchal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/19 11:29:23 by amarchal          #+#    #+#             */
/*   Updated: 2022/01/25 17:45:41 by amarchal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include "./ft_printf/ft_printf.h"
#include "./libft/libft.h"
#include "minitalk.h"


// void	print_msg(int sig)
// {
	// static char	*temp_msg = {0};
	// static int	bit = 0;
	// static int	nb_bit = 0;
	// int			current_size;
	// char		*message;
	
	// if (sig == SIGUSR2)
	// 	bit += 1 << nb_bit;
	// nb_bit++;
	// if (nb_bit == 8)
	// {
	// 	if (bit == '\0')
	// 	{
	// 		ft_printf("%s\n", temp_msg);
	// 		temp_msg[0] = '\0';
	// 	}
	// 	else
	// 	{
	// 		if (temp_msg)
	// 			current_size = ft_strlen(temp_msg);
	// 		else
	// 			current_size = 0;
	// 		message = ft_calloc(1, current_size + 1 + 1);
	// 		if (temp_msg)
	// 			ft_strlcpy(message, temp_msg, current_size + 1);
	// 		message[current_size] = bit;
	// 		if (temp_msg)
	// 		{
	// 			ft_strlcat(temp_msg, message, current_size + 1);
	// 			free(temp_msg);
	// 		}
	// 		temp_msg = ft_strdup(message);
	// 		free(message);
	// 	}
	// 	nb_bit = 0;
	// 	bit = 0;
	// }
// 	kill(signal_pid, SIGUSR1);
// }

void	get_pid(int sig, siginfo_t *info, void *context)
{
	// printf("Signal received\n");
	int			signal_pid;
	static char	*temp_msg = {0};
	static int	bit = 0;
	static int	nb_bit = 0;
	int			current_size;
	char		*message;
	
	signal_pid = info->si_pid;
	// if (signal_pid == 0)
	// 	pause();
	if (sig == SIGUSR2)
		bit += 1 << nb_bit;
	nb_bit++;
	if (nb_bit == 8)
	{
		if (bit == '\0')
		{
			ft_printf("%s\n", temp_msg);
			temp_msg[0] = '\0';
			bit = 0;
			nb_bit = 0;
			
			// pause();
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
	kill(signal_pid, SIGUSR1);
	(void)sig;
	(void)context;
}

int	main(void)
{
	struct sigaction	sa;
	
	// sa.sa_handler = print_msg;
	sa.sa_sigaction = get_pid;
	// sa.sa_mask = 
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = SA_RESTART;
	ft_printf("pid = %d\n", getpid());
	sigaction(SIGUSR1, &sa, NULL);
	sigaction(SIGUSR2, &sa, NULL);
	while (1)
	{
		pause();
	}
}
