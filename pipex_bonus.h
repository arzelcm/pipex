/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arcanava <arcanava@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 17:04:09 by arcanava          #+#    #+#             */
/*   Updated: 2024/04/05 14:16:02 by arcanava         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_BONUS_H
# define PIPEX_BONUS_H

# include "libft/libft.h"
# include <stdio.h>
# include <fcntl.h>

# define PROGRAM_NAME "pipex"
# define ARG_AMOUNT 5
# define FIRST_CMD_ARG_POS 2
# define NEW_FILE_PERMISSIONS 0644
# define NOT_CMD_ARG_AMOUNT 2
# define CHILD_PID 0


typedef struct s_args
{
	char	**argv;
	char	**envp;
	int		argc;
}	t_args;

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

typedef struct s_fds
{
	int	read;
	int	write;
	int	file;
}	t_fds;

char	*get_command_path(char *command, char **envp);

void	error(void);

void	custom_error(char *message);

void	free_matrix(void **matrix);

int		safe_fork(void);

int		safe_open(const char *path, int mode);

int		safe_dup2(int destination_fd, int origin_fd);

int		safe_close(int fd);

char	*safe_ft_strjoin(char const *s1, char const *s2);

void	init_context(t_context *context, int argc, char **argv, char **envp);

void	init_pipe(t_context *context, int i);

void	terminate_pipe(t_context *context, int i, int here_doc);

void	init_fds(t_fds *fds, int read, int write);

#endif