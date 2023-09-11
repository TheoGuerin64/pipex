/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tguerin <tguerin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/03 12:44:00 by tguerin           #+#    #+#             */
/*   Updated: 2022/11/15 16:27:41 by tguerin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	put_flag(char flag, va_list args, int *total_len, int fd)
{
	if (flag == 'c')
		fd_put_char(va_arg(args, int), total_len, fd);
	if (flag == 's')
		fd_put_string(va_arg(args, char *), total_len, fd);
	if (flag == 'p')
		put_ptr(va_arg(args, void *), total_len, fd);
	if (flag == 'd' || flag == 'i')
		put_long((long)va_arg(args, int), total_len, fd);
	if (flag == 'u')
		put_unsigned_int(va_arg(args, unsigned int), total_len, fd);
	if (flag == 'x' || flag == 'X')
		put_hexa(va_arg(args, unsigned int), flag == 'x', total_len, fd);
	if (flag == '%')
		fd_put_char('%', total_len, fd);
}

static int	put_text(const char *format, va_list args, int fd)
{
	int		total_len;
	int		last_is_arg;
	int		i;

	total_len = 0;
	last_is_arg = 0;
	i = 0;
	while (format[i])
	{
		if (!last_is_arg && i > 0 && format[i - 1] == '%'
			&& is_in(format[i], "cspdiuxX%"))
		{
			put_flag(format[i], args, &total_len, fd);
			last_is_arg = 1;
		}
		else
		{
			if (format[i] != '%' || (format[i] == '%'
					&& !is_in(format[i + 1], "cspdiuxX%")))
				fd_put_char(format[i], &total_len, fd);
			last_is_arg = 0;
		}
		i++;
	}
	return (total_len);
}

int	ft_printf(const char *format, ...)
{
	va_list	args;
	int		total_len;

	va_start(args, format);
	total_len = put_text(format, args, 0);
	va_end(args);
	return (total_len);
}

int	ft_fd_printf(int fd, const char *format, ...)
{
	va_list	args;
	int		total_len;

	va_start(args, format);
	total_len = put_text(format, args, fd);
	va_end(args);
	return (total_len);
}
