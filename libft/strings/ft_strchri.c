/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchri.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rileone <rileone@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 22:37:47 by rileone           #+#    #+#             */
/*   Updated: 2024/05/22 22:38:32 by rileone          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strchri(const char *s, int c)
{
	char	*str;
	int		i;
	int		n;

	i = ft_strlen((char *) s) + 1;
	n = 0;
	str = (char *)s;
	if (c > 127)
		c %= 256;
	while (i > 0)
	{
		if (str[n] == c)
			return (n);
		n++;
		i--;
	}
	return (-1);
}