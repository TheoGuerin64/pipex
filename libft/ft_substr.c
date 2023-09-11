/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tguerin <tguerin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/27 18:32:26 by tguerin           #+#    #+#             */
/*   Updated: 2022/09/30 15:41:15 by tguerin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*empty_str(void)
{
	char	*str;

	str = malloc(sizeof(char));
	if (!str)
		return (NULL);
	str[0] = '\0';
	return (str);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*sub;
	size_t	size;
	int		i;

	if (!s)
		return (NULL);
	if (ft_strlen(s) < start)
		return (empty_str());
	size = 0;
	while (s[start + size] && size < len)
		size++;
	sub = malloc(sizeof(char) * (size + 1));
	if (!sub)
		return (NULL);
	i = 0;
	while ((size_t)i < size)
	{
		sub[i] = s[i + start];
		i++;
	}
	sub[i] = '\0';
	return (sub);
}
