/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arcanava <arcanava@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 12:02:52 by arcanava          #+#    #+#             */
/*   Updated: 2024/03/06 18:38:53 by arcanava         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// TODO: Free shit and null-safe!!!!!!!!!!!

#include "pipex.h"

int	exec_command(char *command, char **envp)
{
	char **argv;
	char	*command_path;

	argv = ft_split(command, ' ');
	command_path = get_command_path(argv[0], envp);
	//execve(command_path, argv, envp);
	return (1);
}

int	main(int argc, char **argv, char **envp)
{
	int	i;
	int	input_fd;
	int	pipe_fds[2];
	
	(void) envp;
	if (argc < ARG_MIN_COUNT)
		return (0);
	if (pipe(pipe_fds) == -1)
		return (perror("pipex"), 1);
	i = ARG_FIRST_COMMAND_POS;
	while (i < argc)
	{
		if (i == ARG_FIRST_COMMAND_POS)
		{
			input_fd = open(argv[1], O_RDONLY);
			if (input_fd < 0)
				return (perror("pipex"), 1);
			dup2(STDIN_FILENO, input_fd);
		}
		else 
			dup2(STDIN_FILENO, pipe_fds[0]);
		dup2(STDOUT_FILENO, pipe_fds[1]);
		exec_command(argv[i], envp);
		i++;
	}
	
	/*int fds[2];
	pipe(fds);
	
	
	
	execve("/usr/bin/cat", cmd, envp);
	perror("pipex");*/
	close(input_fd);
	return (0);
}
