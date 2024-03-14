/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arcanava <arcanava@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 12:39:42 by arcanava          #+#    #+#             */
/*   Updated: 2024/03/14 23:22:56 by arcanava         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*get_command_path(char *command, char **envp)
{
	char	*command_path;
	char	**paths;
	char	*path;
	char	*suffix;
	int		i;

	command_path = NULL;
	while (*envp && !command_path)
	{
		command_path = ft_strnstr(*envp, "PATH=", ft_strlen(*envp));
		envp++;
	}
	command_path += 5;
	paths = ft_split(command_path, ':');
	if (!paths)
		error();
	suffix = ft_strjoin(*paths, "/");
	path = ft_strjoin(suffix, command);
	if (!suffix || !path)
		error();
	i = 0;
	while (paths[i] && access(path, F_OK) == -1)
	{
		free(suffix);
		free(path);
		suffix = ft_strjoin(paths[i], "/");
		path = ft_strjoin(suffix, command);
		if (!suffix || !path)
			error();
		i++;
	}
	if (!paths[i])
		path = NULL;
	free(suffix);
	free_matrix((void **) paths);
	return (path);
}

/**
 * @brief 
 * Shows the error and exits the program with EXIT_FAILURE(1)
 */
void	error(void)
{
	perror(PROGRAM_NAME);
	exit(EXIT_FAILURE);
}

/**
 * @brief 
 * Shows the message error and exits the program with EXIT_FAILURE(1)
 * The shown error will be: [$PROGRAM_NAME:$message\n]
 */
void	custom_error(char *message)
{
	dup2(STDERR_FILENO, STDOUT_FILENO);
	ft_printf("%s: %s\n", PROGRAM_NAME, message);
	exit(EXIT_FAILURE);
}

void	free_matrix(void **matrix)
{
	int	i;

	if (matrix)
	{
		i = 0;
		while (*(matrix + i))
			free(*(matrix + i++));
		free(matrix);
	}
}

int	safe_fork(void)
{
	pid_t pid;

	pid = fork();
	if (pid == -1)
		error();
	return (pid);
}

int	safe_open(const char *path, int mode)
{
	int	res;

	res = open(path, mode, FILE_PERMISSIONS);
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
	int res;

	res = close(fd);
	if (res == -1)
		error();
	return (res);
}