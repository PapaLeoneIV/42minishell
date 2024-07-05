/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_cleaner.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rileone <rileone@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 10:40:19 by fgori             #+#    #+#             */
/*   Updated: 2024/07/05 10:50:07 by rileone          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	remove_null_tokens(t_parser *pars)
{
	t_token	*ptr;
	t_token	*tmp;

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
				free(tmp);
		}
		else
			ptr = ptr->next;
	}
}

void	free_tokens(t_token *head)
{
	t_token	*current;
	t_token	*tmp;

	current = head;
	while (current != NULL)
	{
		tmp = current;
		current = current->next;
		free(tmp->value);
		free(tmp);
	}
}
