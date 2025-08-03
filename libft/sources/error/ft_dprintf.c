/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dprintf.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sguan <sguan@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/22 21:26:19 by sguan             #+#    #+#             */
/*   Updated: 2025/07/20 19:06:58 by sguan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	print_str(int fd, char *str)
{
	int	count;

	count = 0;
	if (!str)
		return (write (fd, "(null)", 6));
	while (*str)
	{
		write(fd, str, 1);
		str++;
		count++;
	}
	return (count);
}

int	print_int(int fd, int value)
{
	unsigned int	num;
	int				count;
	char			digit;

	count = 0;
	if (value < 0)
	{
		num = -value;
		count += write(fd, "-", 1);
	}
	else
		num = value;
	if (num < 10)
	{
		digit = num + '0';
		return (count + write(fd, &digit, 1));
	}
	count += print_int(fd, num / 10);
	digit = (num % 10) + '0';
	return (count + write(fd, &digit, 1));
}

int	print_hex(int fd, unsigned int value)
{
	char	*hex_list;
	int		count;
	char	digit;

	count = 0;
	hex_list = "0123456789abcdef";
	if (value < 16)
	{
		digit = hex_list[value % 16];
		write(fd, &digit, 1);
		count++;
	}
	if (value > 15)
	{
		count += print_hex(fd, value / 16);
		digit = hex_list[value % 16];
		write(fd, &digit, 1);
		count++;
	}
	return (count);
}

int	process_format(int fd, const char **format, va_list ap)
{
	int	count;

	count = 0;
	(*format)++;
	if (**format == 's')
		count += print_str(fd, va_arg(ap, char *));
	else if (**format == 'd')
		count += print_int(fd, va_arg(ap, int));
	else if (**format == 'x')
		count += print_hex(fd, va_arg(ap, unsigned int));
	else if (**format == '%')
	{
		write(fd, "%", 1);
		count++;
	}
	return (count);
}

int	ft_dprintf(int fd, const char *format, ...)
{
	va_list	ap;
	int		count;

	count = 0;
	va_start(ap, format);
	if (!format)
		return (-1);
	while (*format)
	{
		if (*format == '%')
			count += process_format(fd, &format, ap);
		else
		{
			write(fd, format, 1);
			count++;
		}
		format++;
	}
	va_end(ap);
	return (count);
}
