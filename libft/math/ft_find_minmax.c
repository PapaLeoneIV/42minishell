/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_find_minmax.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rileone <rileone@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 15:23:13 by rileone           #+#    #+#             */
/*   Updated: 2024/04/14 13:41:26 by rileone          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

int	*ft_findminmax(t_dll_list *stack_a)
{
	t_dll_list	*ptr;
	int			*minmax;
	int			min;
	int			max;

	ptr = stack_a;
	min = INT_MAX;
	max = INT_MIN;
	while (ptr != NULL)
	{
		if (*(int *)ptr->val < min)
			min = *(int *)ptr->val;
		if (*(int *)ptr->val > max)
			max = *(int *)ptr->val;
		ptr = ptr->next;
	}
	minmax = ft_calloc(2, sizeof(int));
	if (minmax == NULL)
		return (NULL);
	minmax[0] = min;
	minmax[1] = max;
	return (minmax);
}
