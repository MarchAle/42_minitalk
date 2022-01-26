/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarchal <amarchal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/19 11:29:08 by amarchal          #+#    #+#             */
/*   Updated: 2022/01/26 16:03:03 by amarchal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

t_struct	g_data;

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

void	send_first_bit(void)
{
	if (g_data.msg[0] & (1 << 0))
	{
		if (kill(g_data.pid, SIGUSR2))
			exit(EXIT_FAILURE);
	}
	else
	{
		if (kill(g_data.pid, SIGUSR1))
			exit(EXIT_FAILURE);
	}
}

void	send_next_bit(int sig)
{
	if (g_data.msg[g_data.i] & (1 << g_data.current_bit))
		kill(g_data.pid, SIGUSR2);
	else
		kill(g_data.pid, SIGUSR1);
	usleep(100);
	g_data.current_bit++;
	if (g_data.current_bit == 8)
	{
		g_data.current_bit = 0;
		g_data.i++;
	}
	(void)sig;
}

void	terminate_process(int sig)
{
	ft_printf("Message received by server\n");
	exit(EXIT_SUCCESS);
	(void)sig;
}

int	main(int ac, char **av)
{
	signal(SIGUSR1, send_next_bit);
	signal(SIGUSR2, terminate_process);
	if (ac == 3)
	{
		if (!ft_check_pid(av[1]))
		{
			ft_printf("Error : incorrect PID\n");
			return (0);
		}
		g_data.pid = ft_atoi(av[1]);
		g_data.i = 0;
		g_data.msg = av[2];
		g_data.current_bit = 1;
		send_first_bit();
		while (1)
			pause();
	}
	else
		ft_printf("Error : wrong number of arguments\n");
	return (0);
}
