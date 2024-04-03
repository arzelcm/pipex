/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initiators_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arcanava <arcanava@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 17:00:54 by arcanava          #+#    #+#             */
/*   Updated: 2024/04/03 18:46:34 by arcanava         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	init_args(t_args *args, int argc, char **argv, char **envp)
{
	args->argc = argc;
	args->argv = argv;
	args->envp = envp;
}

void	init_pipe(t_pipe_fds *pipe_fds, t_args *args, int i)
{
	pipe_fds->prev_read = pipe_fds->fds[0];
	if (i < args->argc - NOT_CMD_ARG_AMOUNT && pipe(pipe_fds->fds) == -1)
		error();
}

void	terminate_pipe(t_pipe_fds *pipe_fds, t_args *args, int i, int here_doc)
{
	if (here_doc && i == 3)
		safe_close(pipe_fds->prev_read);
	if (i != args->argc - NOT_CMD_ARG_AMOUNT)
		safe_close(pipe_fds->fds[1]);
}

void	init_fds(t_fds *fds, int read, int write)
{
	fds->read = read;
	fds->write = write;
}
