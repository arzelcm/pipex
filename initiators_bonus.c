/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initiators_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arcanava <arcanava@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 17:00:54 by arcanava          #+#    #+#             */
/*   Updated: 2024/04/05 14:16:15 by arcanava         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	init_context(t_context *context, int argc, char **argv, char **envp)
{
	context->argc = argc;
	context->argv = argv;
	context->envp = envp;
	context->fds[0] = -1;
	context->fds[1] = -1;
	context->prev_read = -1;
	context->file_fd = -1;
}

void	init_pipe(t_context *context, int i)
{
	context->prev_read = context->fds[0];
	if (i < context->argc - NOT_CMD_ARG_AMOUNT && pipe(context->fds) == -1)
		error();
}

void	terminate_pipe(t_context *context, int i, int here_doc)
{
	if (here_doc && i == 3)
		safe_close(context->prev_read);
	if (i != context->argc - NOT_CMD_ARG_AMOUNT)
		safe_close(context->fds[1]);
}

void	init_fds(t_fds *fds, int read, int write)
{
	fds->read = read;
	fds->write = write;
}
