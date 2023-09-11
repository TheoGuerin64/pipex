/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tguerin <tguerin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 17:19:42 by tguerin           #+#    #+#             */
/*   Updated: 2022/11/17 21:03:35 by tguerin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	free_split(char **split)
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

void	free_cmds(t_cmd **cmds)
{
	int	i;

	if (!cmds)
		return ;
	i = 0;
	while (cmds[i])
	{
		if (cmds[i + 1] || cmds[i]->args)
			free_split(cmds[i]->args);
		free(cmds[i]->path);
		free(cmds[i]);
		i++;
	}
	free(cmds);
}

int	repipe(char **envp, int pipe_fd[2])
{
	close(pipe_fd[0]);
	close(pipe_fd[1]);
	if (pipe(pipe_fd) == -1)
	{
		perror_shell(envp);
		return (0);
	}
	return (1);
}

int	open_pipes(char **envp, int pipe_fds[2][2])
{
	if (pipe(pipe_fds[0]) == -1)
	{
		perror_shell(envp);
		return (0);
	}
	if (pipe(pipe_fds[1]) == -1)
	{
		close(pipe_fds[0][0]);
		close(pipe_fds[0][1]);
		perror_shell(envp);
		return (0);
	}
	return (1);
}

void	close_pipe_fds(int pipe_fds[2][2])
{
	close(pipe_fds[0][0]);
	close(pipe_fds[0][1]);
	close(pipe_fds[1][0]);
	close(pipe_fds[1][1]);
}
