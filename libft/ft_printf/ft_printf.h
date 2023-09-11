/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tguerin <tguerin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 17:05:02 by tguerin           #+#    #+#             */
/*   Updated: 2022/11/15 16:26:54 by tguerin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include "../libft.h"
# include <stdarg.h>
# include <unistd.h>

int		is_in(char c, char const *set);
void	fd_put_char(char c, int *total_len, int fd);
void	fd_put_string(char *s, int *total_len, int fd);
void	put_long(long n, int *total_len, int fd);
void	put_unsigned_int(unsigned int n, int *total_len, int fd);
void	put_hexa(unsigned long n, int isLower, int *total_len, int fd);
void	put_ptr(void *ptr, int *total_len, int fd);

#endif
