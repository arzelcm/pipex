/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arcanava <arcanava@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 12:02:52 by arcanava          #+#    #+#             */
/*   Updated: 2024/04/08 16:59:52 by arcanava         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h" 

void	exec_command(char *command, char **envp, t_context *context)
{
	char	**argv;
	char	*command_path;

	argv = ft_split(command, ' ');
	if (!argv)
		error(context);
	command_path = get_command_path(argv[0], envp, context);
	if (!command_path)
		custom_error(ft_strjoin("command not found: ", argv[0]));
	if (execve(command_path, argv, envp) == -1)
		error(context);
}

void	set_redirections(int i, t_context *context)
{
	t_fds	fds;

	if (i == FIRST_CMD_ARG_POS)
		init_fds(&fds,
			safe_open(context->argv[1], O_RDONLY, context), context->fds[1]);
	else if (i == context->argc - 2)
	{
		init_fds(&fds, context->prev_read,
			safe_open(context->argv[context->argc - 1],
				O_CREAT | O_WRONLY | O_TRUNC, context));
	}
	else
		init_fds(&fds, context->prev_read, context->fds[1]);
	if (i != context->argc - 2)
		safe_close(&context->fds[0], context);
	safe_dup2(fds.read, STDIN_FILENO, context);
	safe_dup2(fds.write, STDOUT_FILENO, context);
	safe_close(&fds.read, context);
	safe_close(&fds.write, context);
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

int	main(int argc, char **argv, char **envp)
{
	t_context	context;
	int			i;
	pid_t		pid;

	if (argc < ARG_AMOUNT)
		custom_error("Missing arguments");
	if (argc > ARG_AMOUNT)
		custom_error("Too many arguments");
	init_context(argc, argv, envp, &context);
	i = 1;
	while (++i < argc - 1)
	{
		init_pipe(i, &context);
		pid = safe_fork(&context);
		if (pid == CHILD_PID)
		{
			set_redirections(i, &context);
			exec_command(argv[i], envp, &context);
		}
		terminate_pipe(i, &context);
	}
	safe_close(&context.fds[0], &context);
	return (wait_child_processes(argc - 3, pid));
}
