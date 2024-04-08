/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arcanava <arcanava@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 12:31:15 by arcanava          #+#    #+#             */
/*   Updated: 2024/02/12 18:19:49 by arcanava         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

int	ft_putstr(char *str, int *count)
{
	while (*str && *count > -1)
	{
		ft_putchar(str, count);
		str++;
	}
	return (*count);
}
