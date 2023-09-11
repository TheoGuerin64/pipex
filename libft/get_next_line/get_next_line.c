/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tguerin <tguerin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/07 17:15:20 by tguerin           #+#    #+#             */
/*   Updated: 2022/11/08 14:50:40 by tguerin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static void	*stop(char *str)
{
	free(str);
	return (NULL);
}

static size_t	strlen_until(const char *s, char c)
{
	size_t	i;

	i = 0;
	while (s[i] && s[i] != c)
		i++;
	return (i);
}

static char	*strnextend(char *s1, char const *s2, int n)
{
	char	*extend;
	int		i;
	int		j;

	extend = malloc(sizeof(char) * (strlen_until(s1, '\0') + n + 1));
	if (!extend)
		return (NULL);
	i = 0;
	while (s1[i])
	{
		extend[i] = s1[i];
		i++;
	}
	j = 0;
	while (s2[j] && j < n)
	{
		extend[i + j] = s2[j];
		j++;
	}
	extend[i + j] = '\0';
	free(s1);
	return (extend);
}

static void	strshift(char *s, int n)
{
	int	total_size;
	int	i;

	if (n == 0)
		return ;
	total_size = strlen_until(s, '\0');
	i = 0;
	while (i < total_size)
	{
		if (i + n < total_size)
		{
			s[i] = s[i + n];
			s[i + n] = 0;
		}
		else
			s[i] = 0;
		i++;
	}
}

char	*ft_get_next_line(int fd)
{
	static char	buffer[BUFFER_SIZE + 1];
	int			line_size;
	ssize_t		read_size;
	char		*str;

	str = ft_strdup("");
	while (buffer[0] != '\n')
	{
		if (buffer[0] == '\0')
		{
			read_size = read(fd, buffer, BUFFER_SIZE);
			if (read_size == -1 || (read_size == 0 && str[0] == '\0'))
				return (stop(str));
			if (read_size == 0)
				return (str);
		}
		line_size = strlen_until(buffer, '\n');
		str = strnextend(str, buffer, line_size);
		if (str == NULL)
			return (stop(str));
		strshift(buffer, line_size);
	}
	strshift(buffer, 1);
	str = strnextend(str, "\n", 1);
	return (str);
}
