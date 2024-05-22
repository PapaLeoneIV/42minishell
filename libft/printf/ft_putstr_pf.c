/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_pf.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rileone <riccardo.leone@student.42fir      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 15:23:13 by rileone           #+#    #+#             */
/*   Updated: 2024/04/02 15:23:18 by rileone          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_putstr_pf(char *str, int *count)
{
	int	i;

	i = 0;
	if (!str)
		str = "(null)";
	while (str[i] != '\0')
	{
		ft_putchar_pf(str[i], count);
		i++;
	}
}
