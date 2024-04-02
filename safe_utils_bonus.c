/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   safe_utils_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arcanava <arcanava@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 16:21:21 by arcanava          #+#    #+#             */
/*   Updated: 2024/04/02 18:13:51 by arcanava         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

int	safe_fork(void)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
		error();
	return (pid);
}

int	safe_open(const char *path, int mode)
{
	int	res;

	res = open(path, mode, NEW_FILE_PERMISSIONS);
	if (res == -1)
		error();
	return (res);
}

int	safe_dup2(int destination_fd, int origin_fd)
{
	int	res;

	res = dup2(destination_fd, origin_fd);
	if (res == -1)
		error();
	return (res);
}

int	safe_close(int fd)
{
	int	res;

	res = close(fd);
	if (res == -1)
		error();
	return (res);
}

char	*safe_ft_strjoin(char const *s1, char const *s2)
{
	char	*res;

	res = ft_strjoin(s1, s2);
	if (!res)
		error();
	return (res);
}
