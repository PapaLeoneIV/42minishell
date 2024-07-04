/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quot_tokenizer_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgori <fgori@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 10:57:52 by fgori             #+#    #+#             */
/*   Updated: 2024/07/04 10:15:15 by fgori            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/lexer.h"

t_token	*check_prev(t_token *token)
{
	t_token	*prev;

	if (!token->prev)
		return (NULL);
	prev = token->prev;
	if (prev == NULL || prev->type == WHITESPACE_TOKEN)
		return (NULL);
	if (prev->type == WORD_TOKEN || prev->type == DOUBLE_QUOTES_TOKEN
		|| prev->type == SING_QUOTES_TOKEN || prev->type == DOLLAR_TOKEN
		|| prev->type == HERDOC_FILENAME_WITHQUOTES)
		return (prev);
	return (NULL);
}

void	join_tokens(t_token **node, t_token **prev)
{
	char	*tmp;

	tmp = (*prev)->value;
	(*prev)->value = ft_strjoin((*prev)->value, (*node)->value);
	if ((*node)->next)
		(*node)->next->prev = (*prev);
	else
		(*prev)->next = NULL;
	(*prev)->next = (*node)->next;
	free((*node)->value);
	free(*node);
	free(tmp);
	*node = NULL;
	*node = *prev;
}

void	join_tokens_values_when_no_space_between(t_parser *pars)
{
	t_token	*prev;
	t_token	*ptr;

	ptr = pars->head;
	while (ptr != NULL)
	{
		prev = check_prev(ptr);
		if (!prev || (prev && prev->type != HERDOC_FILENAME_WITHQUOTES
				&& prev->value && prev->value[0] == '\0'))
		{
			ptr = ptr->next;
			continue ;
		}
		if (ptr && (ptr->type == WORD_TOKEN || ptr->type == SING_QUOTES_TOKEN
				|| ptr->type == DOUBLE_QUOTES_TOKEN
				|| ptr->type == DOLLAR_TOKEN) && prev)
		{
			join_tokens(&ptr, &prev);
		}
		ptr = ptr->next;
	}
}

char	*join_quoted_token_expansion(t_token *head)
{
	char	*out;
	char	*tmp;

	out = NULL;
	while (head)
	{
		tmp = out;
		out = ft_strjoin(out, head->value);
		free(tmp);
		head = head->next;
	}
	return (out);
}
