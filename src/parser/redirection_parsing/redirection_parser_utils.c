/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_parser_utils.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rileone <rileone@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 17:14:31 by rileone           #+#    #+#             */
/*   Updated: 2024/07/05 10:56:14 by rileone          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

t_token	*look_tokens_ahead(t_token *current)
{
	if (current->next == NULL)
		return (NULL);
	if (current->next->type != WORD_TOKEN
		&& current->next->type != HERDOC_FILENAME_WITHQUOTES)
		return (NULL);
	if (current->next->type == WORD_TOKEN)
		return (current->next);
	if (current->next && (current->next->type == WORD_TOKEN
			|| current->next->type == HERDOC_FILENAME_WITHQUOTES))
		return (current->next);
	return (NULL);
}

int	count_pipes(t_token *head)
{
	t_token	*ptr;
	int		counter;

	counter = 0;
	ptr = head;
	while (ptr)
	{
		if (ptr->type == PIPE_TOKEN)
			counter++;
		ptr = ptr->next;
	}
	return (counter);
}

t_token	*split_command_based_on_pipes(t_token **ptr)
{
	t_token	*newlist;
	t_token	*newnode;

	newlist = NULL;
	while (*ptr && (*ptr)->type != PIPE_TOKEN)
	{
		newnode = token_new(NULL);
		newnode->value = ft_strdup((*ptr)->value);
		newnode->type = (*ptr)->type;
		if (!newnode)
		{
			free_tokens(newlist);
			return (NULL);
		}
		token_add_back(&newlist, newnode);
		(*ptr) = (*ptr)->next;
	}
	if ((*ptr) && (*ptr)->type == PIPE_TOKEN)
		(*ptr) = (*ptr)->next;
	return (newlist);
}

static void	redir_all(t_token **redir)
{
	(*redir) = (*redir)->prev;
	(*redir)->next = (*redir)->next->next->next;
	(*redir)->next->prev = (*redir);
}

int	remove_redir(t_token **redir)
{
	int		i;
	t_token	*tmp;

	i = 0;
	tmp = (*redir);
	if ((*redir)->prev && (*redir)->next->next)
	{
		redir_all(redir);
		i++;
	}
	else if (!(*redir)->prev && (*redir)->next->next)
	{
		(*redir) = (*redir)->next->next;
		(*redir)->prev = NULL;
		i += 2;
	}
	else if ((*redir)->prev && !(*redir)->next->next)
	{
		(*redir)->prev->next = NULL;
		*redir = (*redir)->prev;
	}
	else
		return (redirection_clear(&tmp->next), redirection_clear(&tmp), -3);
	return (redirection_clear(&tmp->next), redirection_clear(&tmp), i);
}
