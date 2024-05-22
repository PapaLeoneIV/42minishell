/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dll_insert_head.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rileone <rileone@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 15:23:13 by rileone           #+#    #+#             */
/*   Updated: 2024/04/14 13:49:25 by rileone          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

void	ft_dll_insert_head(t_dll_list **head, t_dll_list *new)
{
	if (*head == NULL)
	{
		*head = new;
		new->next = NULL;
	}
	else
	{
		new->next = *head;
		(*head)->prev = new;
		*head = new;
		ft_dll_update_index(head);
	}
}

/* int main()
{
    int arr[] = {1, -99, 0 , 23, 45};


    t_dll_list* head = ft_dll_initi(arr, 5);
   // t_dll_list* new = ft_dll_new(12); 
   int *val = malloc(sizeof(int));
   *val = 10;
    t_dll_list* newnode = ft_dll_new(val); 
   // printf("newnode value: %i\n", *(int*)newnode->val);


    ft_dll_insert_head(&head, newnode);
    while(head != NULL)
    {
        printf("node values :%i,\n ",  *(int *)head->val ) ;
        head = head->next;
    }
    ft_dll_return_head(&head);
    ft_dll_clear(&head, free);
} */
