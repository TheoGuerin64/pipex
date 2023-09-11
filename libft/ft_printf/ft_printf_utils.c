/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tguerin <tguerin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 22:33:54 by tguerin           #+#    #+#             */
/*   Updated: 2022/11/15 16:27:56 by tguerin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	is_in(char c, char const *set)
{
	int	i;

	i = 0;
	while (set[i])
	{
		if (set[i] == c)
			return (1);
		i++;
	}
	return (0);
}

void	fd_put_char(char c, int *total_len, int fd)
{
	write(fd, &c, 1);
	(*total_len)++;
}

void	fd_put_string(char *s, int *total_len, int fd)
{
	int	len;

	if (!s)
	{
		len = 6;
		write(fd, "(null)", len);
	}
	else
	{
		len = ft_strlen(s);
		write(fd, s, len);
	}
	(*total_len) += len;
}

void	put_long(long n, int *total_len, int fd)
{
	if (n < 0)
	{
		fd_put_char('-', total_len, fd);
		n *= -1;
	}
	if (n < 10)
		fd_put_char(n + '0', total_len, fd);
	else
	{
		put_long(n / 10, total_len, fd);
		put_long(n % 10, total_len, fd);
	}
}

void	put_unsigned_int(unsigned int n, int *total_len, int fd)
{
	if (n < 10)
		fd_put_char(n + '0', total_len, fd);
	else
	{
		put_unsigned_int(n / 10, total_len, fd);
		put_unsigned_int(n % 10, total_len, fd);
	}
}
