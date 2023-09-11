/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tguerin <tguerin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/21 20:59:51 by tguerin           #+#    #+#             */
/*   Updated: 2022/11/17 19:37:08 by tguerin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static char	**get_path(char **envp)
{
	char	**path_clean;
	char	**path;
	char	*tmp;
	int		i;

	i = 0;
	while (envp[i])
	{
		tmp = ft_strnstr(envp[i], "PATH=", ft_strlen(envp[i]));
		if (tmp == envp[i])
		{
			path_clean = ft_split(envp[i] + 5, ':');
			path = split_append(path_clean, "");
			free(path_clean);
			if (!path)
			{
				perror_shell(envp);
				return (NULL);
			}
			return (path);
		}
		i++;
	}
	return (NULL);
}

static char	*parse_cmd_path(char *path, char *cmd, int *error_flag)
{
	char	*tmp;
	char	*cmd_path;

	tmp = ft_strjoin(path, "/");
	if (!tmp)
	{
		*error_flag = 1;
		return (NULL);
	}
	cmd_path = ft_strjoin(tmp, cmd);
	free(tmp);
	if (!cmd_path)
	{
		*error_flag = 1;
		return (NULL);
	}
	if (access(cmd_path, X_OK) == 0)
		return (cmd_path);
	free(cmd_path);
	return (NULL);
}

static char	*get_cmd_path(char **envp, char *cmd, int *error_flag)
{
	char	**path;
	char	*cmd_path;
	int		i;

	path = get_path(envp);
	if (!path)
	{
		*error_flag = 1;
		return (NULL);
	}
	i = 0;
	while (path[i])
	{
		cmd_path = parse_cmd_path(path[i], cmd, error_flag);
		if (cmd_path || *error_flag == 1)
		{
			free_split(path);
			return (cmd_path);
		}
		i++;
	}
	free_split(path);
	*error_flag = 2;
	return (NULL);
}

static t_cmd	*parse_cmd(char **envp, char *raw_cmd)
{
	int		error_flag;
	t_cmd	*cmd;

	error_flag = 0;
	cmd = malloc(sizeof(*cmd));
	if (!cmd)
		return (NULL);
	cmd->args = ft_split(raw_cmd, ' ');
	if (!cmd->args)
	{
		free(cmd);
		return (NULL);
	}
	cmd->path = get_cmd_path(envp, cmd->args[0], &error_flag);
	if (!cmd->path && error_flag == 1)
	{
		free_split(cmd->args);
		free(cmd);
		return (NULL);
	}
	return (cmd);
}

t_cmd	**parse_cmds(char **envp, char **raw_cmds, int cmd_number)
{
	t_cmd	**cmds;
	int		i;

	cmds = ft_calloc(cmd_number + 1, sizeof(*cmds));
	if (!cmds)
	{
		perror_shell(envp);
		return (NULL);
	}
	i = 0;
	while (i < cmd_number)
	{
		cmds[i] = parse_cmd(envp, raw_cmds[i]);
		if (!cmds[i])
		{
			perror_shell(envp);
			free_cmds(cmds);
			return (NULL);
		}
		i++;
	}
	cmds[i] = NULL;
	return (cmds);
}
