/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_analizer.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rileone <rileone@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 11:26:41 by fgori             #+#    #+#             */
/*   Updated: 2024/07/04 12:10:08 by rileone          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

int	check_for_non_valid_char_list(t_token *ptr, char *non_valid_char)
{
	int	i;

	while (ptr)
	{
		i = 0;
		if (ptr->type == DOUBLE_QUOTES_TOKEN || ptr->type == SING_QUOTES_TOKEN
			|| ptr->type == HERDOC_FILENAME_WITHQUOTES)
		{
			ptr = ptr->next;
			continue ;
		}
		while (ptr->value[i] != '\0')
		{
			if (ft_strchr(non_valid_char, ptr->value[i]))
				return (SUCCESS);
			i++;
		}
		ptr = ptr->next;
	}
	return (ERROR);
}

void	change_non_special_tokens_to_word_tokens(t_token *head)
{
	t_token	*ptr;

	ptr = head;
	while (ptr)
	{
		if (ptr->type == DOLLAR_TOKEN || ptr->type == SING_QUOTES_TOKEN
			|| ptr->type == DOUBLE_QUOTES_TOKEN)
			ptr->type = WORD_TOKEN;
		ptr = ptr->next;
	}
}

void	handle_remotion_logic(	t_token	**ptr, t_token **head)
{
	if (((*ptr))->prev == NULL)
	{
		(*head) = ((*ptr))->next;
		((*ptr))->next->prev = NULL;
	}
	else
	{
		if (((*ptr))->next == NULL)
			((*ptr))->prev->next = NULL;
		else
		{
			((*ptr))->next->prev = ((*ptr))->prev;
			((*ptr))->prev->next = ((*ptr))->next;
		}
	}
	free(((*ptr))->value);
	free(((*ptr)));
	(*ptr) = NULL;
}

void	remove_whitespaces(t_token **head)
{
	t_token	*ptr;
	t_token	*tmp;

	ptr = *head;
	tmp = NULL;
	while (ptr)
	{
		if (ptr->type == WHITESPACE_TOKEN)
		{
			tmp = ptr->next;
			handle_remotion_logic(&ptr, head);
			ptr = tmp;
		}
		else
			ptr = ptr->next;
	}
}
