/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_del_lastnode.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rileone <rileone@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 15:23:13 by rileone           #+#    #+#             */
/*   Updated: 2024/04/14 13:58:22 by rileone          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

void	ft_del_lastnode(t_dll_list *list)
{
	t_dll_list	*tmp;

	tmp = list;
	if (!list)
		return ;
	while (tmp != NULL)
	{
		if (tmp->next->next == NULL)
		{
			free(tmp->next);
			tmp->next = NULL;
			return ;
		}
		tmp = tmp->next;
	}
}
