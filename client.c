/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarchal <amarchal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/19 11:29:08 by amarchal          #+#    #+#             */
/*   Updated: 2022/01/24 18:37:52 by amarchal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include "./libft/libft.h"
#include "./ft_printf/ft_printf.h"

void	printf_char(int pid, char c)
{
	int	current_bit;

	current_bit = 0;
	while (current_bit < 8)
	{
		if (c & (1 << current_bit))
			kill(pid, SIGUSR2);		// return 0 if successful
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

int	main(int ac, char **av)
{
	int		i;
	int		pid;
	char	*msg;

	if (ac == 3)
	{
		if (!ft_check_pid(av[1]))
		{
			ft_printf("Error : incorrect PID\n");
			return (0);
		}
		i = 0;
		pid = ft_atoi(av[1]);
		msg = av[2];
		while (msg[i])
		{
			printf_char(pid, msg[i]);
			i++;
		}
		printf_char(pid, msg[i]);
	}
	else
		ft_printf("Error : bad number of arguments\n");
	return (0);
}