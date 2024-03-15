/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arcanava <arcanava@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 12:39:42 by arcanava          #+#    #+#             */
/*   Updated: 2024/03/15 17:27:29 by arcanava         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	**get_possible_paths(char **envp)
{
	char	*command_path;
	char	**paths;

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
	return (paths);
}

char	*get_command_path(char *command, char **envp)
{
	char	**paths;
	char	*path;
	char	*suffix;
	int		i;

	paths = get_possible_paths(envp);
	suffix = safe_ft_strjoin(*paths, "/");
	path = safe_ft_strjoin(suffix, command);
	i = 0;
	while (paths[i] && access(path, F_OK | X_OK) == -1)
	{
		free(suffix);
		free(path);
		suffix = safe_ft_strjoin(paths[i], "/");
		path = safe_ft_strjoin(suffix, command);
		i++;
	}
	if (!paths[i])
		path = NULL;
	free(suffix);
	free_matrix((void **) paths);
	return (path);
}

void	error(void)
{
	perror(PROGRAM_NAME);
	exit(EXIT_FAILURE);
}

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
