/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_base_pointers_help_pf.c                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rileone <rileone@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 15:23:13 by rileone           #+#    #+#             */
/*   Updated: 2024/04/14 13:36:11 by rileone          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	checkerror(char *str)
{
	int		i;
	size_t	j;
	size_t	x;

	x = ft_strlen_pf((const char *)str);
	i = 0;
	if (str[0] == '\0' || x == 1)
		return (0);
	while (str[i] != '\0')
	{
		if (str[i] <= 32 || str[i] == 127 || str[i] == 43 || str[i] == 45)
			return (0);
		j = i + 1;
		while (j < ft_strlen_pf((const char *)str))
		{
			if (str[i] == str[j])
				return (0);
			j++;
		}
		i++;
	}
	return (1);
}

void	ft_putnbr_base_pointers_help_pf(void *nbr, char *base, int *count)
{
	size_t	len;
	int		error;
	size_t	nb;

	error = checkerror(base);
	len = ft_strlen_pf(base);
	nb = (size_t)nbr;
	if (error == 1)
	{
		if (nb < len)
			ft_putchar_pf(base[nb], count);
		if (nb >= len)
		{
			ft_putnbr_base_pointers_help_pf((void *)(nb / len), base, count);
			ft_putnbr_base_pointers_help_pf((void *)(nb % len), base, count);
		}
	}
}
