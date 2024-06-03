/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_cleaner.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rileone <rileone@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 22:08:39 by rileone           #+#    #+#             */
/*   Updated: 2024/06/03 20:25:54 by rileone          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


/**Se l espansione di una variabile non e' stata trovata, 
 * il token->value viene settato a NULL. Questa funzione 
 * serve una volta individuati a rimuoverli dalla lista
*/

void remove_null_tokens(t_parser *pars) {
    t_token *ptr = pars->head;
    t_token *tmp;

    while (ptr) {
        if (ptr->value == NULL) {  // Check if the token's value is NULL
            tmp = ptr;
            ptr = ptr->next;  // Move to the next node before freeing the current node

            // Update the links in the list
            if (tmp->prev != NULL) {
                tmp->prev->next = tmp->next;
            } else {
                // If there is no previous node, we must be at the head
                pars->head = tmp->next;
            }
            if (tmp->next != NULL) {
                tmp->next->prev = tmp->prev;
            }

            // Now we can safely free the current node
            free(tmp);
        } else {
            ptr = ptr->next;  // Move to the next node
        }
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