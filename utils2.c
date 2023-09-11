/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tguerin <tguerin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 17:19:42 by tguerin           #+#    #+#             */
/*   Updated: 2022/11/25 16:36:04 by tguerin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static size_t	split_size(char **split)
{
	size_t	size;

	size = 0;
	while (split[size])
		size++;
	return (size);
}

char	**split_append(char **split, const char *str)
{
	char	**new_split;
	size_t	size;
	int		i;

	if (!split)
		return (NULL);
	size = split_size(split);
	new_split = malloc(sizeof(*new_split) * (size + 2));
	if (!new_split)
		return (NULL);
	i = 0;
	while ((unsigned int)i < size)
	{
		new_split[i] = split[i];
		i++;
	}
	new_split[i] = ft_strdup(str);
	if (!new_split[i])
	{
		free(new_split);
		return (NULL);
	}
	new_split[i + 1] = NULL;
	return (new_split);
}

int	check_file(char **envp, char *path, int option, int show_error)
{
	if (access(path, option))
	{
		if (show_error)
			perror_file(envp, path);
		return (0);
	}
	return (1);
}
