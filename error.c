/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tguerin <tguerin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/21 19:19:10 by tguerin           #+#    #+#             */
/*   Updated: 2022/11/25 16:36:23 by tguerin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	perror_file(char **envp, char *file_path)
{
	char	*tmp1;
	char	*tmp2;

	tmp1 = get_shell(envp);
	if (!tmp1)
	{
		perror("shell");
		return ;
	}
	tmp2 = ft_strjoin(tmp1, ": ");
	free(tmp1);
	if (!tmp2)
	{
		perror("shell");
		return ;
	}
	tmp1 = ft_strjoin(tmp2, file_path);
	free(tmp2);
	if (!tmp1)
	{
		perror("shell");
		return ;
	}
	perror(tmp1);
	free(tmp1);
}

void	perror_shell(char **envp)
{
	char	*shell;

	shell = get_shell(envp);
	if (!shell)
	{
		perror("shell");
		return ;
	}
	perror(shell);
	free(shell);
}

int	put_cmd_not_found(t_files *files, char *cmd_name)
{
	char	*shell;

	shell = get_shell(files->envp);
	if (!shell)
	{
		ft_fd_printf(2, "shell: %s: command not found\n", cmd_name);
		return (1);
	}
	ft_fd_printf(2, "%s: %s: command not found\n", shell, cmd_name);
	free(shell);
	return (1);
}
