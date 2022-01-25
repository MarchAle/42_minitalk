/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarchal <amarchal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/19 11:29:08 by amarchal          #+#    #+#             */
/*   Updated: 2022/01/25 17:56:59 by amarchal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include "./libft/libft.h"
#include "./ft_printf/ft_printf.h"
#include "minitalk.h"

t_struct	data;

void	printf_char(int pid, char c)
{
	int	current_bit;

	current_bit = 0;
	while (current_bit < 8)
	{
		if (c & (1 << current_bit))
			kill(pid, SIGUSR2);
		else
			kill(pid, SIGUSR1);
		usleep(100);
		current_bit++;
	}
}

int	ft_check_pid(char *pid)
{
	int	i;

	i = 0;
	while (pid[i])
	{
		if (pid[i] < '0' || pid[i] > '9')
			return (0);
		i++;
	}
	return (1);
}

void	send_next_bit(int sig)
{
	if (data.msg[data.i] & (1 << data.current_bit))
		kill(data.pid, SIGUSR2);
	else
		kill(data.pid, SIGUSR1);
	// usleep(100);
	data.current_bit++;
	if (data.current_bit == 8)
	{
		data.current_bit = 0;
		if (data.msg[data.i] == '\0')
		{
			exit(EXIT_SUCCESS);
			// kill(getpid(), SIGTERM);
		}
		data.i++;
	}
	(void)sig;
}

int	main(int ac, char **av)
{
	signal(SIGUSR1, send_next_bit);

	if (ac == 3)
	{
		if (!ft_check_pid(av[1]))
		{
			ft_printf("Error : incorrect PID\n");
			return (0);
		}
		data.pid = ft_atoi(av[1]);
		data.i = 0;
		data.msg = av[2];
		data.current_bit = 1;
		// printf("data.msg : %s\n", data.msg);
		// printf("data.pid : %d\n", data.pid);
		// printf("data.i : %d\n", data.i);
		// printf("data.current_bit : %d\n", data.current_bit);
		if (data.msg[0] & (1 << 0))
			kill(data.pid, SIGUSR2);
		else
			kill(data.pid, SIGUSR1);
		while (1)
		{
			pause();
		}
	}
	else
		ft_printf("Error : bad number of arguments\n");
	return (0);
}