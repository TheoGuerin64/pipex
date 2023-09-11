/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tguerin <tguerin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/28 10:21:15 by tguerin           #+#    #+#             */
/*   Updated: 2022/09/30 12:49:24 by tguerin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	is_in(char c, char const *set)
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

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*trim;
	int		begin;
	int		end;
	int		i;

	if (!s1)
		return (NULL);
	begin = 0;
	while (is_in(s1[begin], set))
		begin++;
	end = ft_strlen(s1) - 1;
	while (is_in(s1[end], set))
		end--;
	end++;
	trim = malloc(sizeof(char) * ((end - begin) * (end - begin > 0) + 1));
	if (!trim)
		return (NULL);
	i = 0;
	while (begin + i < end)
	{
		trim[i] = s1[begin + i];
		i++;
	}
	trim[i] = '\0';
	return (trim);
}
