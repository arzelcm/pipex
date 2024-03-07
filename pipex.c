/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arcanava <arcanava@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 12:02:52 by arcanava          #+#    #+#             */
/*   Updated: 2024/03/07 18:07:25 by arcanava         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

// TODO: make it void
int	exec_command(char *command, char **envp)
{
	char	**argv;
	char	*command_path;

	argv = ft_split(command, ' ');
	if (!argv)
		error();
	command_path = get_command_path(argv[0], envp);
	if (!command_path)
		custom_error(ft_strjoin(argv[0], ": Command not found."));
	if (command_path)
		free(command_path);
	if (argv)
		free_matrix((void **) argv);
	execve(command_path, argv, envp);
	return (1);
}

int	main(int argc, char **argv, char **envp)
{
	int		i;
	int		input_fd;
	int		pipe_fds[2];
	int		dup1_res;
	int		dup2_res;
	int		close1_res;
	int		close2_res;
	pid_t	pid;
	pid_t	parent_pid;

	if (argc < ARG_MIN_COUNT)
		custom_error("Missing arguments");
	i = ARG_FIRST_COMMAND_POS;
	parent_pid = 0;
	while (i < argc - 1)
	{
		pid = fork();
		if (pid == -1)
			error();
		else if (pid == 0)
		{
			if (!parent_pid)
				parent_pid = pid;
			i++;
			continue;
		}
		if (i == ARG_FIRST_COMMAND_POS)
		{
			input_fd = open(argv[1], O_RDONLY);
			if (pipe(pipe_fds) == -1 || input_fd < 0)
				error();
			dup1_res = dup2(input_fd, STDIN_FILENO);
			dup2_res = dup2(pipe_fds[1], STDOUT_FILENO);
			close1_res = close(input_fd);
			close2_res = close(pipe_fds[1]);
			if (dup1_res == -1 || dup2_res == -1 || close1_res == -1 || close2_res == -1)
				error();
		}
		else if (i == argc - 2)
		{
			waitpid(parent_pid, NULL, 0);
			input_fd = open(argv[argc - 1], O_TRUNC | O_WRONLY);
			if (input_fd < 0)
				error();
			dup1_res = dup2(pipe_fds[0], STDIN_FILENO);
			dup2_res = dup2(input_fd, STDOUT_FILENO);
			close1_res = close(pipe_fds[0]);
			close2_res = close(input_fd);
			if (dup1_res == -1 || dup2_res == -1 || close1_res == -1 || close2_res == -1)
			{
				ft_printf("pipe_fd[0]: %i, dup1_res: %i, dup2_res: %i, close1_res: %i, close2_res: %i", pipe_fds[0], dup1_res, dup2_res, close1_res, close2_res);
				error();
			}
		}
		else
		{
			dup1_res = dup2(pipe_fds[0], STDIN_FILENO);
			close1_res = close(pipe_fds[0]);
			ft_printf("CREATING:pipe_fd[0]: %i\n", pipe_fds[0]);
			if (pipe(pipe_fds) == -1)
				error();
			dup2_res = dup2(pipe_fds[1], STDOUT_FILENO);
			close2_res = close(pipe_fds[1]);
			if (dup1_res == -1 || dup2_res == -1 || close1_res == -1 || close2_res == -1)
				error();
		}
		exec_command(argv[i], envp);
	}
	return (0);
}
