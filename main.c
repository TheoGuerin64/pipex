/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tguerin <tguerin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 16:14:56 by tguerin           #+#    #+#             */
/*   Updated: 2022/11/25 18:57:27 by tguerin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	init_files(int argc, char **argv, t_files *files, int is_here_doc)
{
	int	open_mode;

	files->input_path = NULL;
	if (!is_here_doc)
	{
		files->input_path = argv[1];
		files->input = open(files->input_path, O_RDONLY);
	}
	files->output_path = argv[argc - 1];
	if (is_here_doc)
		open_mode = O_WRONLY | O_APPEND | O_CREAT;
	else
		open_mode = O_WRONLY | O_TRUNC | O_CREAT;
	files->output = open(files->output_path, open_mode, 0644);
}

static void	close_files(t_files *files)
{
	if (files->input != -1)
		close(files->input);
	if (files->output != -1)
		close(files->output);
}

static char	*get_lim(char **argv, int is_here_doc)
{
	char	*lim;

	if (is_here_doc)
		lim = argv[2];
	else
		lim = NULL;
	return (lim);
}

int	main(int argc, char **argv, char **envp)
{
	t_files	files;
	t_cmd	**cmds;
	char	*lim;
	int		return_value;
	int		is_here_doc;

	is_here_doc = 0;
	if (argc > 2)
		is_here_doc = (ft_strncmp(argv[1], "here_doc", 9) == 0);
	if (argc < 5 + is_here_doc)
	{
		ft_fd_printf(2, "Error: Not enough arguments\n");
		return (1);
	}
	files.envp = envp;
	init_files(argc, argv, &files, is_here_doc);
	lim = get_lim(argv, is_here_doc);
	cmds = parse_cmds(envp, argv + 2 + is_here_doc, argc - 3 - is_here_doc);
	if (cmds)
		return_value = exec_cmds(&files, cmds, argc - 3 - is_here_doc, lim);
	else
		return_value = EXIT_FAILURE;
	close_files(&files);
	free_cmds(cmds);
	return (return_value);
}
