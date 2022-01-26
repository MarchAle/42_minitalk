/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minitalk.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarchal <amarchal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/19 16:43:59 by amarchal          #+#    #+#             */
/*   Updated: 2022/01/26 15:22:35 by amarchal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINITALK_H
# define MINITALK_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <signal.h>
# include "./ft_printf/ft_printf.h"
# include "./libft/libft.h"

typedef struct s_struct
{
	int		pid;
	int		i;
	char	*msg;
	int		current_bit;
}	t_struct;

void	add_char(char **temp_msg, char bit);
void	print_msg(int sig, siginfo_t *info, void *context);
int		ft_check_pid(char *pid);
void	send_first_bit(void);
void	send_next_bit(int sig);
void	terminate_process(int sig);

#endif
