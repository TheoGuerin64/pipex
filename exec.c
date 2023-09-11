/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tguerin <tguerin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/25 15:35:50 by tguerin           #+#    #+#             */
/*   Updated: 2022/11/25 16:45:31 by tguerin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static int	wait_cmds(t_cmd **cmds, t_files *files)
{
	int	exit_status;
	int	status;
	int	i;

	i = 0;
	while (cmds[i])
	{
		if (cmds[i]->path)
		{
			waitpid(cmds[i]->pid, &status, 0);
			if (WIFEXITED(status))
				exit_status = WEXITSTATUS(status);
			else if (WIFSIGNALED(status))
				exit_status = WTERMSIG(status);
		}
		else
			exit_status = 127;
		i++;
	}
	if (!check_file(files->envp, files->output_path, W_OK, 0))
		return (1);
	return (exit_status);
}

static int	exec_cmd(t_cmd **cmds, t_files *files, int cmd_number, int i)
{
	cmds[i]->pid = fork();
	if (cmds[i]->pid == -1)
	{
		perror_shell(files->envp);
		return (0);
	}
	else if (cmds[i]->pid == 0)
	{
		if (i == 0 && files->input_path)
			dup2(files->input, 0);
		else
			dup2(files->pipe_fds[(i + 1) % 2][0], 0);
		if (i == cmd_number - 1)
			dup2(files->output, 1);
		else
			dup2(files->pipe_fds[i % 2][1], 1);
		close_pipe_fds(files->pipe_fds);
		execve(cmds[i]->path, cmds[i]->args, files->envp);
		exit(EXIT_FAILURE);
	}
	return (1);
}

static void	here_doc(char *lim, int write_fd)
{
	char	*line;
	int		lim_size;

	lim_size = ft_strlen(lim);
	while (1)
	{
		line = ft_get_next_line(0);
		if (!line || (ft_strncmp(line, lim, lim_size) == 0
				&& lim_size == (int)ft_strlen(line) - 1))
			break ;
		ft_putstr_fd(line, write_fd);
		free(line);
	}
}

static int	check_file_at(t_files *files, char *lim, int cmd_number, int i)
{
	if (i == 0 && !lim)
		return (!check_file(files->envp, files->input_path, R_OK, 1));
	else if (i == cmd_number - 1)
		return (!check_file(files->envp, files->output_path, W_OK, 1));
	return (0);
}

int	exec_cmds(t_files *files, t_cmd **cmds, int cmd_number, char *lim)
{
	int	i;
	int	exit_status;

	if (!open_pipes(files->envp, files->pipe_fds))
		return (EXIT_FAILURE);
	if (lim)
		here_doc(lim, files->pipe_fds[1][1]);
	i = 0;
	while (cmds[i])
	{
		if (!repipe(files->envp, files->pipe_fds[i % 2]))
			return (EXIT_FAILURE);
		if (check_file_at(files, lim, cmd_number, i)
			|| (!cmds[i]->path && put_cmd_not_found(files, cmds[i]->args[0])))
		{
			i++;
			continue ;
		}
		if (!exec_cmd(cmds, files, cmd_number, i))
			return (EXIT_FAILURE);
		i++;
	}
	close_pipe_fds(files->pipe_fds);
	exit_status = wait_cmds(cmds, files);
	return (exit_status);
}
