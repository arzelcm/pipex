/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arcanava <arcanava@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 17:04:09 by arcanava          #+#    #+#             */
/*   Updated: 2024/04/08 16:09:42 by arcanava         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "libft/libft.h"
# include <stdio.h>
# include <fcntl.h>

# define PROGRAM_NAME "pipex"
# define ARG_AMOUNT 5
# define FIRST_CMD_ARG_POS 2
# define NEW_FILE_PERMISSIONS 0644
# define NOT_CMD_ARG_AMOUNT 2
# define CHILD_PID 0

typedef struct s_fds
{
	int	read;
	int	write;
}	t_fds;

typedef struct s_context
{
	char	**argv;
	char	**envp;
	int		argc;
	int		fds[2];
	int		prev_read;
	int		file_fd;
	int		i;
}	t_context;

char	*get_command_path(char *command, char **envp, t_context *context);

void	error(t_context *context);

void	custom_error(char *message);

void	free_matrix(void **matrix);

int		safe_fork(t_context *context);

int		safe_open(const char *path, int mode, t_context *context);

int		safe_dup2(int destination_fd, int origin_fd, t_context *context);

int		safe_close(int *fd, t_context *context);

char	*safe_ft_strjoin(char const *s1, char const *s2, t_context *context);

void	init_context(int argc, char **argv, char **envp, t_context *context);

void	init_pipe(int i, t_context *context);

void	terminate_pipe(int i, t_context *context);

void	init_fds(t_fds *fds, int read, int write);

void	terminate_context(t_context *context);

#endif