/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   safe_utils_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arcanava <arcanava@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 16:21:21 by arcanava          #+#    #+#             */
/*   Updated: 2024/04/05 15:38:58 by arcanava         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

int	safe_fork(t_context *context)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
		error(context);
	return (pid);
}

int	safe_open(const char *path, int mode, t_context *context)
{
	int	res;

	res = open(path, mode, NEW_FILE_PERMISSIONS);
	if (res == -1)
		error(context);
	return (res);
}

int	safe_dup2(int destination_fd, int origin_fd, t_context *context)
{
	int	res;

	res = dup2(destination_fd, origin_fd);
	if (res == -1)
		error(context);
	return (res);
}

int	safe_close(int *fd, t_context *context)
{
	int	res;

	if (*fd == -1)
		return (-1);
	res = close(*fd);
	if (res == -1)
		error(context);
	*fd = -1;
	return (res);
}

char	*safe_ft_strjoin(char const *s1, char const *s2, t_context *context)
{
	char	*res;

	res = ft_strjoin(s1, s2);
	if (!res)
		error(context);
	return (res);
}
