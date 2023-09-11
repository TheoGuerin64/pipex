/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_utils2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tguerin <tguerin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/07 00:49:16 by tguerin           #+#    #+#             */
/*   Updated: 2022/11/15 16:26:12 by tguerin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	put_hexa(unsigned long n, int isLower, int *total_len, int fd)
{
	if (n < 16)
	{
		if (n > 9)
			fd_put_char(n - 10 + 'A' + 32 * isLower, total_len, fd);
		else
			fd_put_char(n + '0', total_len, fd);
	}
	else
	{
		put_hexa(n / 16, isLower, total_len, fd);
		put_hexa(n % 16, isLower, total_len, fd);
	}
}

void	put_ptr(void *ptr, int *total_len, int fd)
{
	unsigned long	n;

	n = (unsigned long)ptr;
	if (n == 0)
	{
		fd_put_string("(nil)", total_len, fd);
		return ;
	}
	fd_put_string("0x", total_len, fd);
	put_hexa(n, 1, total_len, fd);
}
