/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rileone <rileone@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 15:23:13 by rileone           #+#    #+#             */
/*   Updated: 2024/04/14 13:42:04 by rileone          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	char	*ptr;
	size_t	x;
	size_t	n;

	x = 0;
	n = 0;
	ptr = (char *)big;
	if (*little == '\0')
		return (ptr);
	while (big[n] != '\0' && (n < len))
	{
		x = 0;
		if (big[n] == little[x])
		{
			while (big[n + x] == little[x] && (n + x) < len)
			{
				if (little[x + 1] == '\0')
					return (&ptr[n]);
				x++;
			}
		}
		n++;
	}
	return (0);
}
