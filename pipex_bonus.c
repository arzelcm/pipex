/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arcanava <arcanava@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 12:02:52 by arcanava          #+#    #+#             */
/*   Updated: 2024/04/03 19:28:07 by arcanava         ###   ########.fr       */
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

void	set_redirections(int i, t_pipe_fds *pipe_fds, t_args *args, int heredoc)
{
	t_fds	fds;
	int		open_mode;

	if (i == FIRST_CMD_ARG_POS)
		init_fds(&fds, safe_open(args->argv[1], O_RDONLY), pipe_fds->fds[1]);
	else if (i == args->argc - 2)
	{
		open_mode = O_CREAT | O_WRONLY | O_TRUNC;
		if (heredoc)
			open_mode = O_CREAT | O_WRONLY | O_APPEND;
		fds.file = safe_open(args->argv[args->argc - 1], open_mode);
		init_fds(&fds, pipe_fds->prev_read, fds.file);
	}
	else
		init_fds(&fds, pipe_fds->prev_read, pipe_fds->fds[1]);
	if (i != args->argc - 2)
		safe_close(pipe_fds->fds[0]);
	safe_dup2(fds.read, STDIN_FILENO);
	safe_dup2(fds.write, STDOUT_FILENO);
	safe_close(fds.read);
	safe_close(fds.write);
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
	char	*normalized_limiter;

	if (ft_strcmp(argv[*i], "here_doc") != EQUAL_STRINGS)
		return (0);
	if (pipe(pipe_fds->fds) == -1)
		error();
	(*i)++;
	normalized_limiter = safe_ft_strjoin(argv[*i], "\n");
	line = "";
	while (line != NULL
		&& ft_strcmp(normalized_limiter, line) != EQUAL_STRINGS)
	{
		ft_printf("> ");
		line = get_next_line(STDIN_FILENO);
		if (write(pipe_fds->fds[1], line, ft_strlen(line)) == -1)
			error();
	}
	safe_close(pipe_fds->fds[1]);
	free(normalized_limiter);
	return (1);
}

int	main(int argc, char **argv, char **envp)
{
	int			i;
	t_pipe_fds	pipe_fds;
	pid_t		pid;
	t_args		args;
	int			here_doc;

	if (argc < ARG_AMOUNT)
		custom_error("Missing arguments");
	i = 1;
	init_args(&args, argc, argv, envp);
	here_doc = handle_heredoc(&i, argv, &pipe_fds);
	while (++i < argc - 1)
	{
		init_pipe(&pipe_fds, &args, i);
		pid = safe_fork();
		if (pid == CHILD_PID)
		{
			set_redirections(i, &pipe_fds, &args, here_doc);
			exec_command(argv[i], envp);
		}
		terminate_pipe(&pipe_fds, &args, i, here_doc);
	}
	safe_close(pipe_fds.fds[0]);
	return (wait_child_processes(argc - 3, pid));
}
