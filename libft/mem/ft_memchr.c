/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rileone <riccardo.leone@student.42fir      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 15:23:13 by rileone           #+#    #+#             */
/*   Updated: 2024/04/02 15:23:17 by rileone          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	char	*a;
	char	c1;

	a = (char *)s;
	c1 = (char)c;
	while (n > 0)
	{
		if (*a == c1)
			return (a);
		a++;
		n--;
	}
	return (NULL);
}
/*
int	main(void)
{
	int	tab[];

    tab[] = {0, 1, 2 ,3 ,4 ,5};
	printf("%ls",tab + 2);
	if(ft_memchr(tab, 2 + 256, 3) == tab + 2)
		printf("nicenicenicenice");
	else 
		printf("non nice dude");
}

*/
