/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_cleaner.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgori <fgori@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 22:08:39 by rileone           #+#    #+#             */
/*   Updated: 2024/06/04 12:02:46 by fgori            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**Se l espansione di una variabile non e' stata trovata, 
 * il token->value viene settato a NULL. Questa funzione 
 * serve una volta individuati a rimuoverli dalla lista
*/

void remove_null_tokens(t_parser *pars) {
    t_token *ptr;
    t_token *tmp;

    ptr = pars->head;
    while (ptr) 
    {
        if (ptr->value == NULL)
        {  
            tmp = ptr;
            ptr = ptr->next;  
            if (tmp->prev != NULL)
                tmp->prev->next = tmp->next;
            else
                pars->head = tmp->next;
            if (tmp->next != NULL)
                tmp->next->prev = tmp->prev;
            free(tmp);
        } 
        else
            ptr = ptr->next;  
    }
}


void free_tokens(t_token *head)
{
	t_token *current;
	t_token *tmp;

	current = head;
	while (current != NULL)
	{
		tmp = current;
		current = current->next;
		free(tmp->value);
		free(tmp);
	}
}