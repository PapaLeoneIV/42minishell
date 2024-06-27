/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoinchar.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rileone <rileone@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 19:17:53 by rileone           #+#    #+#             */
/*   Updated: 2024/05/01 19:18:09 by rileone          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoinchar(char *str, char c)
{
	int		len;
	char	*out;
	int		i;

	i = 0;
	len = ft_strlen(str);
	out = ft_calloc(len + 2, sizeof(char));
	while (i < len)
	{
		out[i] = str[i];
		i++;
	}
	out[i++] = c;
	free(str);
	return (out);
}
