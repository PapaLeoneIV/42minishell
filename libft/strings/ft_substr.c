/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rileone <rileone@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 15:23:13 by rileone           #+#    #+#             */
/*   Updated: 2024/06/03 16:35:06 by rileone          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char *s, int start, int len)
{
	char	*res;
	int	s_len;

	s_len = ft_strlen(s);
	if (len > s_len)
		len = s_len;
	if (start > s_len)
	{
		len = 0;
		start = s_len;
	}
	if (start + len > s_len)
		len = s_len - start;
	res = ft_calloc(len + 1, sizeof(char));
	if (!res)
		return (NULL);
	ft_memcpy(res, &s[start], len);
	return (res);
}
/*
int	main(void)
{
	char	*str;
    char *str1;
	size_t	size;

	str = "";
    size = 343434;
    str1 = ft_substr(str, 43, size);
    if(!str1)
    printf("questa e' la sottostringa : %s\n", str1);
}
*/
/*
Parameters ????????????
s: The string from which to create the substring.
start: The start index of the substring in the
string ’s’.
len: The maximum length of the substring


Description"""""""""
Allocates (with malloc(3)) and returns a substring
from the string ’s’.
The substring begins at index ’start’ and is of
maximum size ’len’.
*/
