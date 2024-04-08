/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_flags_utils_bonus.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arcanava <arcanava@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 19:52:15 by arcanava          #+#    #+#             */
/*   Updated: 2024/02/28 16:59:40 by arcanava         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	is_flag(char c)
{
	return (c == '#' || c == '+' || c == ' '
		|| c == '-' || c == '0');
}

int	is_hex_spec(char c)
{
	return (c == 'x' || c == 'X');
}

int	is_number_spec(char c)
{
	return (c == 'd' || c == 'i' || c == 'u');
}
