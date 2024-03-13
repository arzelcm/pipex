/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arcanava <arcanava@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 17:04:09 by arcanava          #+#    #+#             */
/*   Updated: 2024/03/13 23:04:29 by arcanava         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "libft/libft.h"
// TODO: Remove?
# include <unistd.h>
# include <stdio.h>
# include <fcntl.h>
# include <stdlib.h>
# include <sys/wait.h>
 #include <errno.h>

# define PROGRAM_NAME "pipex"
# define ARG_MIN_COUNT 5
# define ARG_FIRST_COMMAND_POS 2
# define FILE_PERMISSIONS 0644

// TODO: Create utils.h
char	*get_command_path(char *command, char **envp);
void	error(void);
void	custom_error(char *message);
void	free_matrix(void **matrix);
int		safe_fork(void);
int		safe_open(const char *, int);

#endif