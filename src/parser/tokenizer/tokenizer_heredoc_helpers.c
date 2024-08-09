/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_heredoc_helpers.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rileone <rileone@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/05 10:27:50 by rileone           #+#    #+#             */
/*   Updated: 2024/07/05 10:28:18 by rileone          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "minishell.h"

int	traverse_list_backword_for_heredoc(t_token *last_node)
{
	if (last_node->prev == NULL)
		return (false);
	while (last_node->type == WHITESPACE_TOKEN && last_node != NULL)
		last_node = last_node->prev;
	if (last_node->type == HEREDOC_TOKEN)
		return (true);
	else
		return (false);
}

int	look_behind_for_heredoc(t_token *head)
{
	t_token	*last;
	t_token	*ptr;

	ptr = head;
	last = get_last_token(ptr);
	if (!last)
		return (false);
	if (traverse_list_backword_for_heredoc(last))
		return (true);
	return (false);
}
