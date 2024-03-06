/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arcanava <arcanava@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 12:39:42 by arcanava          #+#    #+#             */
/*   Updated: 2024/03/06 18:18:11 by arcanava         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*get_command_path(char *command, char **envp)
{
	char	*command_path;
	char	**paths;
	char	*path;

	command_path = NULL;
	while (*envp && !command_path)
	{
		command_path = ft_strnstr(*envp, "PATH=", ft_strlen(*envp));
		envp++;
	}
	command_path += 5;
	paths = ft_split(command_path, ':');
	path = ft_strjoin(ft_strjoin(*paths, "/"), command);
	while (*paths && !access(path, F_OK))
	{
		path = ft_strjoin(ft_strjoin(*paths, "/"), command);
		paths++;
	}
	ft_printf("%s\n", path);
	return (0);
}