/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarchal <amarchal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/14 14:38:16 by amarchal          #+#    #+#             */
/*   Updated: 2022/01/26 15:57:50 by amarchal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./ft_printf.h"

int	ft_printf(const char *format, ...)
{
	int			i;
	int			count;
	va_list		args;

	va_start (args, format);
	i = 0;
	count = 0;
	while (format[i])
	{
		if (format[i] == '%')
		{
			if (!format[i + 1])
				return (count);
			if (format[i + 1] == '%')
				count += write(1, "%", 1);
			else
				ft_print_format(args, format[i + 1], &count);
			i++;
		}
		else
			count += write(1, &format[i], 1);
		i++;
	}
	va_end (args);
	return (count);
}

void	ft_print_format(va_list args, char c, int *pt_count)
{
	if (c == 'c')
		*pt_count += ft_putchar(va_arg(args, int));
	else if (c == 's')
		*pt_count += ft_putstr(va_arg(args, char *));
	else if (c == 'd' || c == 'i')
		*pt_count += ft_putnbr_base(va_arg(args, int), "0123456789");
	else if (c == 'x')
		*pt_count += ft_putnbr_base(va_arg(args, unsigned int),
				"0123456789abcdef");
	else if (c == 'X')
		*pt_count += ft_putnbr_base(va_arg(args, unsigned int),
				"0123456789ABCDEF");
	else
		*pt_count += write(1, &c, 1);
}
