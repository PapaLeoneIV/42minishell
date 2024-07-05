/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rileone <rileone@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 15:23:13 by rileone           #+#    #+#             */
/*   Updated: 2024/06/21 12:26:54 by rileone          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s)
{
	int		length;
	char	*arr;
	int		i;

	i = 0;
	length = ft_strlen(s);
	arr = (char *)malloc(sizeof(char) * (length + 1));
	if (!arr)
		return (NULL);
	while (i < length)
	{
		arr[i] = s[i];
		i++;
	}
	arr[i] = '\0';
	return (arr);
}
