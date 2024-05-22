/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_cleaner.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rileone <rileone@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 22:08:39 by rileone           #+#    #+#             */
/*   Updated: 2024/05/22 22:09:17 by rileone          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


/**Se l espansione di una variabile non e' stata trovata, 
 * il token->value viene settato a NULL. Questa funzione 
 * serve una volta individuati a rimuoverli dalla lista
*/

void remove_null_tokens(t_parser *pars)
{
	t_token *ptr;
	t_token *tmp;

	ptr = pars->head;
	while(ptr)
	{
		if (ptr == NULL)
			break;
		if (ptr && ptr->value == NULL)
		{
			tmp = ptr;
			if (ptr->prev != NULL)
				ptr->prev->next = ptr->next;
			if (ptr->next != NULL)
				ptr->next->prev = ptr->prev;
			free(tmp);
			tmp = NULL;
		}
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