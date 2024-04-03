/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arcanava <arcanava@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 17:04:09 by arcanava          #+#    #+#             */
/*   Updated: 2024/04/03 19:53:17 by arcanava         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <stdio.h>
# include <fcntl.h>
# include "libft/libft.h"

# define PROGRAM_NAME "pipex"
# define ARG_AMOUNT 5
# define FIRST_CMD_ARG_POS 2
# define NEW_FILE_PERMISSIONS 0644
# define NOT_CMD_ARG_AMOUNT 2
# define CHILD_PID 0

typedef struct s_pipe_fds
{
	int	fds[2];
	int	prev_read;
}	t_pipe_fds;

char	*get_command_path(char *command, char **envp);

void	error(void);

void	custom_error(char *message);

void	free_matrix(void **matrix);

int		safe_fork(void);

int		safe_open(const char *path, int mode);

int		safe_dup2(int destination_fd, int origin_fd);

int		safe_close(int fd);

char	*safe_ft_strjoin(char const *s1, char const *s2);

#endif