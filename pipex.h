/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arcanava <arcanava@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 17:04:09 by arcanava          #+#    #+#             */
/*   Updated: 2024/03/06 14:20:48 by arcanava         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "libft/libft.h"
// TODO: Remove?
# include <unistd.h>
# include <stdio.h>
# include <fcntl.h>

# define ARG_MIN_COUNT 5
# define ARG_FIRST_COMMAND_POS 2

char	*get_command_path(char *command, char **envp);

#endif