/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arcanava <arcanava@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 12:02:52 by arcanava          #+#    #+#             */
/*   Updated: 2024/03/14 23:24:28 by arcanava         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

// TODO: Refactor, check unused functions, check error prints sometimes collapse
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
	if (execve(command_path, argv, envp) == -1)
		error();
}

void	set_cmd_funnel(int	i, int prev_read_fd, int pipe_fds[2], char **argv, int argc)
{
	int		file_fd;

	if (i == ARG_FIRST_COMMAND_POS)
	{
		file_fd = safe_open(argv[1], O_RDONLY);
		safe_dup2(file_fd, STDIN_FILENO);
		safe_dup2(pipe_fds[1], STDOUT_FILENO);
		safe_close(file_fd);
		safe_close(pipe_fds[1]);
	}
	else if (i == argc - 2)
	{
		file_fd = safe_open(argv[argc - 1], O_CREAT | O_WRONLY | O_TRUNC);
		safe_dup2(prev_read_fd, STDIN_FILENO);
		safe_dup2(file_fd, STDOUT_FILENO);
		safe_close(prev_read_fd);
		safe_close(file_fd);
	}
	else
	{
		safe_dup2(prev_read_fd, STDIN_FILENO);
		safe_close(prev_read_fd);
		safe_dup2(pipe_fds[1], STDOUT_FILENO);
		safe_close(pipe_fds[1]);
	}
}

int	wait_child_processes(int child_amount, int last_pid)
{
	int	exit_status;
	int	i;
	int	child_status;

	exit_status = 0;
	i = 0;
	while (i < child_amount)
	{
		if (last_pid == wait(&child_status))
			exit_status = WEXITSTATUS(child_status);
		i++;
	}
	return (exit_status);
}

int	main(int argc, char **argv, char **envp)
{
	int		i;
	int		pipe_fds[2];
	int		prev_read_fd;
	pid_t	pid;
	int		exit_status;

	if (argc < ARG_MIN_COUNT)
		custom_error("Missing arguments");
	i = ARG_FIRST_COMMAND_POS;
	while (i < argc - 1)
	{
		prev_read_fd = pipe_fds[0];
		if (i != argc - NOT_CMD_ARG_COUNT && pipe(pipe_fds) == -1)
			error();
		pid = safe_fork();
		if (pid == 0)
		{
			set_cmd_funnel(i, prev_read_fd, pipe_fds, argv, argc);
			exec_command(argv[i], envp);
		}
		close(pipe_fds[1]);
		i++;
	}
	exit_status = wait_child_processes(argc - NOT_CMD_ARG_COUNT - 1, pid);
	return (exit_status);
}
