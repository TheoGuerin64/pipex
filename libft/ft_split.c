/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tguerin <tguerin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/28 10:50:33 by tguerin           #+#    #+#             */
/*   Updated: 2022/10/19 17:25:04 by tguerin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	free_split(char **split)
{
	int	i;

	if (!split)
		return ;
	i = 0;
	while (split[i])
	{
		free(split[i]);
		i++;
	}
	free(split);
}

static void	append(char ***split, char *str)
{
	char	**new_split;
	size_t	size;
	int		i;

	size = 0;
	while ((*split)[size])
		size++;
	new_split = malloc(sizeof(char *) * (size + 2));
	if (!new_split)
	{
		free(*split);
		*split = NULL;
		return ;
	}
	i = 0;
	while ((size_t)i < size)
	{
		new_split[i] = (*split)[i];
		i++;
	}
	new_split[i] = str;
	new_split[i + 1] = NULL;
	free(*split);
	*split = new_split;
}

static size_t	size_part(const char *s, char c)
{
	int	i;

	i = 0;
	while (s[i] && s[i] != c)
		i++;
	return (i);
}

static int	cpy_part(char ***split, const char *s, int i, char c)
{
	size_t	part_size;
	char	*str;
	int		j;

	part_size = size_part(s + i, c);
	str = malloc(sizeof(char) * (part_size + 1));
	if (!str)
	{
		free_split(*split);
		return (-1);
	}
	j = 0;
	while ((s + i)[j] && (s + i)[j] != c)
	{
		str[j] = (s + i)[j];
		j++;
	}
	str[j] = '\0';
	append(split, str);
	return (part_size);
}

char	**ft_split(char const *s, char c)
{
	char	**string;
	int		part_size;
	int		i;

	if (!s)
		return (NULL);
	string = malloc(sizeof(char *));
	if (!string)
		return (NULL);
	string[0] = NULL;
	i = 0;
	while (s[i])
	{
		if (s[i] != c)
		{
			part_size = cpy_part(&string, s, i, c);
			if (part_size < 0)
				return (NULL);
			i += part_size;
		}
		else
			i++;
	}
	return (string);
}
