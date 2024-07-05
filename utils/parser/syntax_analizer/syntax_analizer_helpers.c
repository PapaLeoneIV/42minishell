/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_analizer_helpers.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rileone <rileone@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 11:13:30 by fgori             #+#    #+#             */
/*   Updated: 2024/07/05 10:57:21 by rileone          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/lexer.h"

int	handle_pipe_synt_error_tokens(t_token *ptr)
{
	if (ptr->next == NULL || ptr->prev == NULL)
	{
		write(2, "Syntax error near unexpected token '|'\n", 40);
		return (ERROR);
	}
	if (ptr->next->type != WORD_TOKEN
		&& ptr->next->type != HERDOC_FILENAME_WITHQUOTES
		&& ptr->next->type != GREATER_TOKEN && ptr->next->type != LESSER_TOKEN
		&& ptr->next->type != REDIR_OUT_TOKEN
		&& ptr->next->type != HEREDOC_TOKEN)
	{
		write(2, "Syntax error near unexpected token '|'\n", 40);
		return (ERROR);
	}
	return (SUCCESS);
}

int	headle_heredoc_syntax_error_tokens(t_token *ptr)
{
	if (ptr->next && (ptr->next->type == WORD_TOKEN
			|| ptr->next->type == HERDOC_FILENAME_WITHQUOTES))
		return (SUCCESS);
	write(2, "Syntax error near unexpected token '<<'\n", 40);
	return (ERROR);
}

int	handle_redirout_synt_error_tokens(t_token *ptr)
{
	t_token	*tmp;

	tmp = ptr;
	if (tmp->next == NULL)
	{
		write(2, "Syntax error near unexpected token '>'\n", 40);
		return (ERROR);
	}
	else if (tmp->prev && tmp->prev->type == WORD_TOKEN
		&& ft_isnumber(tmp->prev->value))
	{
		write(2, "Syntax error near unexpected token '>'\n", 40);
		return (ERROR);
	}
	else if (tmp->next->type == WORD_TOKEN)
		return (SUCCESS);
	write(2, "Syntax error near unexpected token '>'\n", 40);
	return (ERROR);
}

int	handle_greater_synt_error_tokens(t_token *ptr)
{
	t_token	*tmp;

	tmp = ptr;
	if (tmp->next == NULL)
	{
		write(2, "Syntax error near unexpected token '>'\n", 40);
		return (ERROR);
	}
	else if (tmp->prev && tmp->prev->type == WORD_TOKEN
		&& ft_isnumber(tmp->prev->value))
	{
		write(2, "Syntax error near unexpected token '>'\n", 40);
		return (ERROR);
	}
	else if (tmp->next->type == WORD_TOKEN)
		return (SUCCESS);
	write(2, "Syntax error near unexpected token '>'\n", 40);
	return (ERROR);
}

int	handle_lesser_synt_error_tokens(t_token *ptr)
{
	t_token	*tmp;

	tmp = ptr;
	if (tmp->next == NULL)
	{
		write(2, "Syntax error near unexpected token '<'\n", 40);
		return (ERROR);
	}
	else if (tmp->next->type == WORD_TOKEN)
		return (SUCCESS);
	write(2, "Syntax error near unexpected token '<'\n", 40);
	return (ERROR);
}
