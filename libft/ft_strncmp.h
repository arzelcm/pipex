/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arcanava <arcanava@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 13:07:25 by arcanava          #+#    #+#             */
/*   Updated: 2024/04/02 13:13:12 by arcanava         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_STRNCMP_H
# define FT_STRNCMP_H

# define EQUAL_STRINGS 0

# include <stddef.h>

int	ft_strncmp(const char *s1, const char *s2, size_t n);

int	ft_strcmp(const char *s1, const char *s2);

#endif