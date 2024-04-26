/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_find_min.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rileone <rileone@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 15:23:13 by rileone           #+#    #+#             */
/*   Updated: 2024/04/14 13:41:22 by rileone          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_find_min(t_dll_list *a)
{
	int			min;
	int			idx;
	t_dll_list	*ptr;

	min = INT_MAX;
	ptr = a;
	while (ptr != NULL)
	{
		if (*(int *)ptr->val < min)
		{
			min = *(int *)ptr->val;
			idx = ptr->index;
		}
		ptr = ptr->next;
	}
	return (idx);
}
