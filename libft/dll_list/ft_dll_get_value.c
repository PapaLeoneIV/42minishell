/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dll_get_value.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rileone <rileone@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 15:23:13 by rileone           #+#    #+#             */
/*   Updated: 2024/04/14 13:51:21 by rileone          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

int	ft_dll_get_value(t_dll_list *list, int index)
{
	int			i;
	t_dll_list	*ptr;

	i = 0;
	ptr = list;
	if (!list)
		return (-1);
	while (i < index)
	{
		if (ptr == NULL)
			return (-1);
		i++;
		ptr = ptr->next;
	}
	return (*(int *)(ptr->val));
}

/* int main()
{
    int arr[] = {0, 99, 23, 354, 46};
    int len = 5;

    t_dll_list* list = ft_dll_initi(arr, len);
    if(ft_dll_get_value(list, 2) > ft_dll_get_value(list, 0))
        printf("res : %i\n", 9999);
    else 
        printf("res non esiste");
}  */
