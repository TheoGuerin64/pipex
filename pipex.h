/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tguerin <tguerin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 16:15:08 by tguerin           #+#    #+#             */
/*   Updated: 2022/11/25 16:59:07 by tguerin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "libft/libft.h"
# include <sys/wait.h>
# include <stdlib.h>
# include <fcntl.h>
# include <stdio.h>

typedef struct s_cmd
{
	char	**args;
	char	*path;
	int		pid;
}		t_cmd;

typedef struct s_files
{
	int		pipe_fds[2][2];
	char	*input_path;
	int		input;
	char	*output_path;
	int		output;
	char	**envp;
}		t_files;

void	free_split(char **split);
void	perror_file(char **envp, char *file_path);
int		put_cmd_not_found(t_files *files, char *cmd_name);
char	*get_shell(char **envp);
void	free_cmds(t_cmd **cmds);
t_cmd	**parse_cmds(char **envp, char **raw_cmds, int cmd_number);
int		repipe(char **envp, int pipe_fd[2]);
void	close_pipe_fds(int pipe_fds[2][2]);
void	perror_shell(char **envp);
int		open_pipes(char **envp, int pipe_fds[2][2]);
char	**split_append(char **split, const char *str);
int		check_file(char **envp, char *path, int option, int show_error);
int		exec_cmds(t_files *files, t_cmd **cmds, int cmd_number, char *lim);

#endif
