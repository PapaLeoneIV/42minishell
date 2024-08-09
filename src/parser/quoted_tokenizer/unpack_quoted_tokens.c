/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unpack_quoted_tokens.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgori <fgori@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 10:14:57 by fgori             #+#    #+#             */
/*   Updated: 2024/07/04 10:15:43 by fgori            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

static void	null_token(t_token *ptr, t_token **head, t_token *tmp)
{
	if (!ptr->prev)
	{
		(*head) = ptr->next;
		if (ptr->next)
			ptr->next->prev = NULL;
	}
	else
	{
		if (ptr->next == NULL)
			ptr->prev->next = NULL;
		else
		{
			ptr->prev->next = ptr->next;
			ptr->next->prev = ptr->prev;
		}
	}
	free(ptr->value);
	free(ptr);
	ptr = NULL;
	ptr = tmp;
}

void	unpack_quoted_tokens(t_token **head, t_shell *shell)
{
	t_token		*ptr;
	t_parser	*list;
	t_token		*tmp;

	ptr = *head;
	tmp = NULL;
	while (ptr != NULL)
	{
		tmp = ptr->next;
		if (ptr->type == DOUBLE_QUOTES_TOKEN)
		{
			list = tokenize_quoted_values(ptr, shell);
			if (list == NULL)
				null_token(ptr, head, tmp);
			else
			{
				free(ptr->value);
				ptr->value = join_quoted_token_expansion(list->head);
				free_tokens(list->head);
				free(list);
			}
		}
		ptr = tmp;
	}
}
