/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arcanava <arcanava@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 11:30:09 by arcanava          #+#    #+#             */
/*   Updated: 2024/02/28 17:00:12 by arcanava         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	init_flags(t_state *state)
{
	state->has_flags = 0;
	state->hex_prefix = 0;
	state->force_sign = 0;
	state->empty_sign = 0;
	state->justify_left = 0;
	state->padding_char = ' ';
	state->width = 0;
	state->precision = -1;
	state->precision_len = 0;
	state->buffer_len = 0;
	state->num = 0;
}

int	ft_printf(const char *s, ...)
{
	t_state	state;

	va_start(state.arg_lst, s);
	state.s = s;
	state.count = 0;
	while (*state.s)
	{
		init_flags(&state);
		if (*state.s == '%')
			apply_format(&state);
		else
			ft_putchar(state.s, &state.count);
		if (state.count == -1)
			return (-1);
		state.s++;
	}
	va_end(state.arg_lst);
	return (state.count);
}
