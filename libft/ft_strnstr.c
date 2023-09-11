/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tguerin <tguerin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/27 13:17:55 by tguerin           #+#    #+#             */
/*   Updated: 2022/09/30 15:40:58 by tguerin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	i;
	size_t	j;

	if (*little == '\0')
		return ((char *)big);
	i = 0;
	while (len && big[i])
	{
		j = 0;
		while (big[i + j] && j < len + (len + 1 != 0))
		{
			if (little[j] == '\0')
				return ((char *)(big + i));
			if (little[j] != big[i + j])
				break ;
			j++;
		}
		if (little[j] == '\0' && j < len + (len + 1 != 0))
			return ((char *)(big + i));
		len--;
		i++;
	}
	return (NULL);
}
