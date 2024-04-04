/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arcanava <arcanava@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 10:10:34 by arcanava          #+#    #+#             */
/*   Updated: 2024/03/22 18:49:32 by arcanava         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_chrcmp(unsigned char c1, unsigned char c2)
{
	return (c1 - c2);
}

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n && ft_chrcmp(s1[i], s2[i]) == 0
		&& s1[i] != '\0' && s2[i] != '\0')
		i++;
	if (i == n)
		return (0);
	else
		return (ft_chrcmp(s1[i], s2[i]));
}

int	ft_strcmp(const char *s1, const char *s2)
{
	size_t	i;

	i = 0;
	while (ft_chrcmp(s1[i], s2[i]) == 0
		&& s1[i] != '\0' && s2[i] != '\0')
		i++;
	return (ft_chrcmp(s1[i], s2[i]));
}
