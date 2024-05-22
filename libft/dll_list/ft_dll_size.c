/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dll_size.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rileone <rileone@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 15:23:13 by rileone           #+#    #+#             */
/*   Updated: 2024/04/14 13:50:00 by rileone          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

int	ft_dll_size(t_dll_list *head)
{
	int			length;
	t_dll_list	*ptr;

	ptr = head;
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
