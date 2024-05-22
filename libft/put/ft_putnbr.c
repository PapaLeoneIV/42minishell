/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rileone <rileone@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 15:23:13 by rileone           #+#    #+#             */
/*   Updated: 2024/04/14 13:38:17 by rileone          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr(int n)
{
	char		c;
	long long	nl;

	nl = (long long)n;
	if (nl < 0)
	{
		nl *= -1;
		write(1, "-", 1);
	}
	if (nl >= 10)
	{
		ft_putnbr((nl / 10));
	}
	c = (unsigned int)(nl % 10) + '0';
	write(1, &c, 1);
}
