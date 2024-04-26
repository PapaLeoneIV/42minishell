/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_clear_mtx.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rileone <rileone@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 15:23:13 by rileone           #+#    #+#             */
/*   Updated: 2024/04/14 13:41:33 by rileone          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_clear_mtx(char ***mtx, int len)
{
	int	i;

	i = 0;
	if (!mtx || !(*mtx) || !(**mtx))
		return ;
	while (i < len)
	{
		free(*(*mtx + i));
		*(*mtx + i) = NULL;
		i++;
	}
	free(*(mtx));
	*(mtx) = NULL;
}
