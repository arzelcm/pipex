/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initiators_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arcanava <arcanava@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 17:00:54 by arcanava          #+#    #+#             */
/*   Updated: 2024/04/05 15:37:22 by arcanava         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	init_context(int argc, char **argv, char **envp, t_context *context)
{
	context->argc = argc;
	context->argv = argv;
	context->envp = envp;
	context->fds[0] = -1;
	context->fds[1] = -1;
	context->prev_read = -1;
	context->file_fd = -1;
}

void	terminate_context(t_context *context)
{
	if (!context)
		return ;
	safe_close(&context->fds[0], NULL);
	safe_close(&context->fds[1], NULL);
	safe_close(&context->prev_read, NULL);
	safe_close(&context->file_fd, NULL);
}

void	init_pipe(int i, t_context *context)
{
	context->prev_read = context->fds[0];
	if (i < context->argc - NOT_CMD_ARG_AMOUNT && pipe(context->fds) == -1)
		error(context);
}

void	terminate_pipe(int i, int here_doc, t_context *context)
{
	if (here_doc && i == 3)
		safe_close(&context->prev_read, context);
	if (i != context->argc - NOT_CMD_ARG_AMOUNT)
		safe_close(&context->fds[1], context);
}

void	init_fds(t_fds *fds, int read, int write)
{
	fds->read = read;
	fds->write = write;
}
