/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dll_clear.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rileone <rileone@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 15:23:13 by rileone           #+#    #+#             */
/*   Updated: 2024/04/14 13:36:43 by rileone          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

void	ft_dll_clear(t_dll_list **lst, void (*del)(void *))
{
	t_dll_list	*ptr;
	t_dll_list	*temp;

	if (!*lst || !lst || !del)
		return ;
	ptr = (*lst);
	ft_dll_return_head(&ptr);
	while (ptr != NULL)
	{
		temp = ptr;
		ptr = temp->next;
		free(temp->val);
		free(temp);
	}
	*lst = NULL;
}
