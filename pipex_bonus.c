/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arcanava <arcanava@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 12:02:52 by arcanava          #+#    #+#             */
/*   Updated: 2024/04/02 19:22:39 by arcanava         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

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

void	set_redirections(int i, t_pipe_fds *pipe_fds, char **argv, int argc)
{
	int		file_fd;
	int		read_fd;
	int		write_fd;

	if (i == FIRST_CMD_ARG_POS)
	{
		file_fd = safe_open(argv[1], O_RDONLY);
		read_fd = file_fd;
		write_fd = pipe_fds->fds[1];
	}
	else if (i == argc - 2)
	{
		file_fd = safe_open(argv[argc - 1], O_CREAT | O_WRONLY | O_TRUNC);
		read_fd = pipe_fds->prev_read;
		write_fd = file_fd;
	}
	else
	{
		read_fd = pipe_fds->prev_read;
		write_fd = pipe_fds->fds[1];
	}
	safe_dup2(read_fd, STDIN_FILENO);
	safe_close(read_fd);
	safe_dup2(write_fd, STDOUT_FILENO);
	safe_close(write_fd);
}

int	wait_child_processes(int child_amount, int last_pid)
{
	int	exit_status;
	int	child_status;
	int	i;

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

int	handle_heredoc(int *i, char **argv, t_pipe_fds *pipe_fds)
{
	char	*line;

	(void) i;
	if (ft_strcmp(argv[*i], "here_doc") != EQUAL_STRINGS)
		return (0);
	if (pipe(pipe_fds->fds) == -1)
		error();
	(*i)++;
	line = get_next_line(STDIN_FILENO);
	while (line != NULL
		&& (ft_strncmp(argv[*i], line, ft_strlen(line) - 1) != EQUAL_STRINGS || ft_strlen(line) <= 1))
	{
		write(pipe_fds->fds[1], line, ft_strlen(line));
		line = get_next_line(STDIN_FILENO);
	}
	safe_close(pipe_fds->fds[1]);
	return (1);
}

int	main(int argc, char **argv, char **envp)
{
	int			i;
	t_pipe_fds	pipe_fds;
	pid_t		pid;
	int			exit_status;
	int			here_doc;

	if (argc < ARG_AMOUNT)
		custom_error("Missing arguments");
	i = 1;
	here_doc = handle_heredoc(&i, argv, &pipe_fds);
	while (++i < argc - 1)
	{
		pipe_fds.prev_read = pipe_fds.fds[0];
		if (i != argc - NOT_CMD_ARG_AMOUNT && pipe(pipe_fds.fds) == -1)
			error();
		pid = safe_fork();
		if (pid == CHILD_PID)
		{
			set_redirections(i, &pipe_fds, argv, argc);
			exec_command(argv[i], envp);
		}
		safe_close(pipe_fds.fds[1]);
	}
	exit_status = wait_child_processes(argc - NOT_CMD_ARG_AMOUNT - 1, pid);
	return (exit_status);
}
