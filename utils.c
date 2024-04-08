/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arcanava <arcanava@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 12:39:42 by arcanava          #+#    #+#             */
/*   Updated: 2024/04/08 16:22:34 by arcanava         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	**get_possible_paths(char **envp, t_context *context)
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
		error(context);
	return (paths);
}

char	*get_command_path(char *command, char **envp, t_context *context)
{
	char	**paths;
	char	*path;
	char	*suffix;
	int		i;

	paths = get_possible_paths(envp, context);
	suffix = safe_ft_strjoin(*paths, "/", context);
	path = safe_ft_strjoin(suffix, command, context);
	i = 0;
	while (paths[i] && access(path, F_OK | X_OK) == -1)
	{
		free(suffix);
		free(path);
		suffix = safe_ft_strjoin(paths[i], "/", context);
		path = safe_ft_strjoin(suffix, command, context);
		i++;
	}
	if (!paths[i])
		path = NULL;
	free(suffix);
	free_matrix((void **) paths);
	return (path);
}

void	error(t_context *context)
{
	perror(PROGRAM_NAME);
	terminate_context(context);
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
