/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_base.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarchal <amarchal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/07 20:00:15 by amarchal          #+#    #+#             */
/*   Updated: 2022/01/26 16:00:20 by amarchal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./ft_printf.h"

int	ft_putnbr_base(long long nbr, char *base)
{
	int			size;
	long long	base_size;

	size = 1;
	if (nbr < 0)
	{
		size++;
		nbr *= -1;
		write(1, "-", 1);
	}
	base_size = ft_strlen(base);
	if (nbr >= base_size)
		size += ft_putnbr_base((nbr / base_size), base);
	ft_putchar(base[nbr % base_size]);
	return (size);
}
