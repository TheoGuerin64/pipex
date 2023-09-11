/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tguerin <tguerin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/28 12:19:38 by tguerin           #+#    #+#             */
/*   Updated: 2022/10/06 23:46:50 by tguerin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	get_len(long value)
{
	int	len;

	len = 1;
	while (value / 10 > 0)
	{
		len++;
		value /= 10;
	}
	return (len);
}

char	*ft_itoa(int n)
{
	char	*str;
	long	value;
	int		len;
	int		i;

	value = n;
	if (n < 0)
		value *= -1;
	len = get_len(value);
	str = malloc(sizeof(char) * ((n < 0) + len + 1));
	if (!str)
		return (NULL);
	i = 0;
	if (n < 0)
		str[i++] = '-';
	len += i;
	while (i < len)
	{
		str[len - i - (n >= 0)] = value % 10 + '0';
		value /= 10;
		i++;
	}
	str[i] = '\0';
	return (str);
}
