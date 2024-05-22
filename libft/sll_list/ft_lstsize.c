/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   z.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rileone <riccardo.leone@student.42fir      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 15:23:13 by rileone           #+#    #+#             */
/*   Updated: 2024/04/02 15:23:18 by rileone          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	z(t_list *lst)
{
	int		length;
	t_list	*ptr;

	ptr = lst;
	length = 0;
	if (!ptr)
		return (0);
	while (ptr->next != NULL)
	{
		length++;
		ptr = ptr->next;
	}
	if (ptr->next == NULL)
		length++;
	return (length);
}
