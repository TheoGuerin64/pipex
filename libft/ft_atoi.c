/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tguerin <tguerin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/27 13:35:09 by tguerin           #+#    #+#             */
/*   Updated: 2022/10/06 22:57:10 by tguerin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_atoi(const char *nptr)
{
	int	result;
	int	old_result;
	int	sign;
	int	i;

	i = 0;
	while (nptr[i] == ' ' || (nptr[i] >= 9 && nptr[i] <= 13))
		i++;
	sign = 1;
	if (nptr[i] == '-')
		sign = -1;
	if (nptr[i] == '-' || nptr[i] == '+')
		i++;
	result = 0;
	old_result = 0;
	while (ft_isdigit(nptr[i]))
	{
		result *= 10;
		if (result / 10 != old_result)
			return (-1 + (sign == -1));
		result += nptr[i] - '0';
		old_result = result;
		i++;
	}
	return (result * sign);
}
