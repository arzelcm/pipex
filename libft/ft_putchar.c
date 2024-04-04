/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putchar.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arcanava <arcanava@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 21:06:22 by arcanava          #+#    #+#             */
/*   Updated: 2024/02/07 20:09:41 by arcanava         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

int	ft_putchar(const char *c, int *counter)
{
	if (write(1, c, 1) == -1)
		*counter = -1;
	else
		(*counter)++;
	return (*counter);
}
