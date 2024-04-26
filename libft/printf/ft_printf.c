/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rileone <rileone@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 15:23:13 by rileone           #+#    #+#             */
/*   Updated: 2024/04/14 13:39:49 by rileone          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_printf(char const *str, ...)
{
	va_list	ap;
	int		count;

	count = 0;
	va_start(ap, str);
	if (!str)
	{
		return (0);
	}
	while (*str)
	{
		if (*str != '%')
		{
			ft_putchar_pf(*str, &count);
			str++;
		}
		else if (*str++ == '%')
		{
			ft_process_variable(*str, ap, &count);
			str++;
		}
	}
	va_end(ap);
	return (count);
}
