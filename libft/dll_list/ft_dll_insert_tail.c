/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dll_insert_tail.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rileone <rileone@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 15:23:13 by rileone           #+#    #+#             */
/*   Updated: 2024/04/14 13:49:21 by rileone          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

void	ft_dll_insert_tail(t_dll_list **head, t_dll_list *new)
{
	t_dll_list	*temp;

	if (*head == NULL)
	{
		*head = new;
		return ;
	}
	ft_dll_return_tail(head);
	temp = *head;
	temp->next = new;
	new->prev = temp;
	new->next = NULL;
	new->index = (temp->index) + 1;
	ft_dll_return_head(head);
}
