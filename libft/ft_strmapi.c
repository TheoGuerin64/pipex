/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tguerin <tguerin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/28 16:32:25 by tguerin           #+#    #+#             */
/*   Updated: 2022/09/30 14:36:29 by tguerin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char			*new_s;
	unsigned int	i;

	if (!s)
		return (NULL);
	new_s = ft_strdup(s);
	if (!new_s)
		return (NULL);
	i = 0;
	while (s[i])
	{
		new_s[i] = f(i, s[i]);
		i++;
	}
	return (new_s);
}
