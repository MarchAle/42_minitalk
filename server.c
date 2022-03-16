/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarchal <amarchal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/19 11:29:23 by amarchal          #+#    #+#             */
/*   Updated: 2022/02/28 13:31:32 by amarchal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

void	add_char(char **temp_msg, char bit)
{
	int		current_size;
	char	*message;

	current_size = 0;
	if (*temp_msg)
		current_size = ft_strlen(*temp_msg);
	message = ft_calloc(1, current_size + 1 + 1);
	if (!message)
		exit(EXIT_FAILURE);
	if (*temp_msg)
		ft_strlcpy(message, *temp_msg, current_size + 1);
	message[current_size] = bit;
	if (*temp_msg)
	{
		ft_strlcat(*temp_msg, message, current_size + 1);
		free(*temp_msg);
	}
	*temp_msg = ft_strdup(message);
	if (!*temp_msg)
		exit(EXIT_FAILURE);
	free(message);
}

void	print_msg(int sig, siginfo_t *info, void *context)
{
	static char	*temp_msg = {0};
	static int	bit = 0;
	static int	nb_bit = 0;

	usleep(100);
	if (sig == SIGUSR2)
		bit += 1 << nb_bit;
	nb_bit++;
	if (nb_bit == 8)
	{
		if (bit == '\0')
		{
			ft_printf("%s\n", temp_msg);
			temp_msg[0] = '\0';
			if (kill(info->si_pid, SIGUSR2))
				exit(EXIT_FAILURE);
		}
		else
			add_char(&temp_msg, bit);
		nb_bit = 0;
		bit = 0;
	}
	if (kill(info->si_pid, SIGUSR1))
		exit(EXIT_FAILURE);
	(void)context;
}

int	main(void)
{
	struct sigaction	sa;

	sa.sa_sigaction = print_msg;
	sa.sa_flags = SA_RESTART;
	sigemptyset(&sa.sa_mask);
	sigaddset(&sa.sa_mask, SIGUSR1);
	sigaddset(&sa.sa_mask, SIGUSR2);
	sigaction(SIGUSR1, &sa, NULL);
	sigaction(SIGUSR2, &sa, NULL);
	ft_printf("Server PID : %d\n", getpid());
	while (1)
		pause();
}
