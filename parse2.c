/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tguerin <tguerin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 18:24:47 by tguerin           #+#    #+#             */
/*   Updated: 2022/11/17 19:08:20 by tguerin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static char	*parse_shell(char *s)
{
	char	**shell_split;
	char	*tmp;
	int		i;

	shell_split = ft_split(s + 6, '/');
	if (!shell_split)
	{
		free_split(shell_split);
		return (NULL);
	}
	i = 0;
	while (shell_split[i + 1])
		i++;
	tmp = ft_strdup(shell_split[i]);
	free_split(shell_split);
	return (tmp);
}

char	*get_shell(char **envp)
{
	char	*tmp;
	int		i;

	i = 0;
	while (envp[i])
	{
		tmp = ft_strnstr(envp[i], "SHELL=", ft_strlen(envp[i]));
		if (tmp == envp[i])
			return (parse_shell(tmp));
		i++;
	}
	return (NULL);
}
