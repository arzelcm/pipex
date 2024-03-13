/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arcanava <arcanava@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 12:02:52 by arcanava          #+#    #+#             */
/*   Updated: 2024/03/12 21:17:41 by arcanava         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

// TODO: make it void
void	exec_command(char *command, char **envp)
{
	char	**argv;
	char	*command_path;

	argv = ft_split(command, ' ');
	if (!argv)
		error();
	command_path = get_command_path(argv[0], envp);
	if (!command_path)
		custom_error(ft_strjoin("command not found: ", argv[0]));
	if (command_path)
		free(command_path);
	if (argv)
		free_matrix((void **) argv);
	if (execve(command_path, argv, envp) == -1)
		error();
}

void	set_cmd_funnel(int	i, int prev_read_fd, int pipe_fds[2], char **argv, int argc)
{
	int		file_fd;
	int		dup1_res;
	int		dup2_res;
	int		close1_res;
	int		close2_res;

	if (i == ARG_FIRST_COMMAND_POS)
		{
			file_fd = safe_open(argv[1], O_RDONLY);
			dup1_res = dup2(file_fd, STDIN_FILENO);
			dup2_res = dup2(pipe_fds[1], STDOUT_FILENO);
			close1_res = close(file_fd);
			close2_res = close(pipe_fds[1]);
			if (dup1_res == -1 || dup2_res == -1 || close1_res == -1 || close2_res == -1)
				error();
		}
		else if (i == argc - 2)
		{
			file_fd = safe_open(argv[argc - 1], O_TRUNC | O_WRONLY);
			dup1_res = dup2(pipe_fds[0], STDIN_FILENO);
			dup2_res = dup2(file_fd, STDOUT_FILENO);
			close1_res = close(pipe_fds[0]);
			close2_res = close(file_fd);
			if (dup1_res == -1 || dup2_res == -1 || close1_res == -1 || close2_res == -1)
				error();
		}
		else
		{
			dup1_res = dup2(prev_read_fd, STDIN_FILENO);
			close1_res = close(prev_read_fd);
			dup2_res = dup2(pipe_fds[1], STDOUT_FILENO);
			close2_res = close(pipe_fds[1]);
			if (dup1_res == -1 || dup2_res == -1 || close1_res == -1 || close2_res == -1)
				error();
		}
}

int	main(int argc, char **argv, char **envp)
{
	int		i;
	int		pipe_fds[2];
	int		prev_read_fd;
	pid_t	pid;

	if (argc < ARG_MIN_COUNT)
		custom_error("Missing arguments");
	i = ARG_FIRST_COMMAND_POS;
	while (i < argc - 1)
	{
		prev_read_fd = pipe_fds[0];
		if (i != argc - 2 && pipe(pipe_fds) == -1)
			error();
		pid = safe_fork();
		if (pid == 0)
		{
			set_cmd_funnel(i, prev_read_fd, pipe_fds, argv, argc);
			exec_command(argv[i], envp);
		}
		else
			i++;
	}
	i = 0;
	while (i < argc - 3 && pid > 0)
	{
		pid = wait(NULL);
		ft_printf("Process(%i) was finished with exit(%i)\n", (int) pid, errno);
		// TODO: Wait for child processess to return correct exit status
		i++;
	}
	return (0);
}
