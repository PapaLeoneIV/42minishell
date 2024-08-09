/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quot_tokenizer.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rileone <rileone@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 10:59:07 by fgori             #+#    #+#             */
/*   Updated: 2024/07/13 10:39:39 by rileone          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

t_parser	*tokenize_quoted_values(t_token *node, t_shell *shell)
{
	t_parser	*parser;

	if (node && !(node->value))
		return (NULL);
	parser = ft_calloc(1, sizeof(t_parser));
	init_parser_quot(parser);
	while (node->value[parser->count])
	{
		parser->char_type = get_char_type_quoted(node->value[parser->count]);
		if (parser->state == STATE_GENERAL)
			general_state_handler_quoted(node->value, parser);
		else if (parser->state == STATE_DOLLAR
			&& ((parser->char_type != REG_CHAR
					&& parser->char_type != DIGIT_CHAR)
				|| (parser->char_type == DIGIT_CHAR
					&& node->value[parser->count - 1] == '$')))
			dollar_state_handler_quoted(node->value, parser, shell);
		if (node->value[parser->count + 1] == '\0'
			&& !slice_end_token(node->value, parser, shell))
			return (free(parser), free_tokens(parser->head), NULL);
		parser->count++;
	}
	if (parser->head == NULL)
		return (free(parser), NULL);
	return (parser);
}

void	general_state_handler_quoted(char *stringa, t_parser *pars)
{
	char	next;

	next = -1;
	if (pars->char_type == WHITESPACE_CHAR || pars->char_type == DOLLAR_CHAR)
	{
		if (stringa[pars->count + 1])
			next = get_char_type(stringa, pars, pars->count + 1);
		if (pars->char_type == DOLLAR_CHAR && next == WHITESPACE_CHAR)
		{
			slice_token_string_doll_spec_case(stringa, pars);
			return ;
		}
		if (pars->count > pars->start)
			slice_token_string(stringa, pars);
		if (pars->char_type == WHITESPACE_CHAR)
			slice_single_char_token(stringa, pars);
		if (pars->char_type == DOLLAR_CHAR)
			check_and_change_status(&pars->state, pars->char_type, pars);
	}
}

void	dollar_state_handler_quoted_if_clause(char *stringa,
		t_parser *pars, t_shell *shell)
{
	char	*status;

	if ((pars->count > pars->start && pars->char_type == QUESTION_MARK_CHAR
			&& stringa[pars->count - 1] == '$'))
	{
		set_values(stringa, pars, DOLLAR_TOKEN);
		if (strcmp(pars->token->value, "$?") == 0)
		{
			status = ft_itoa(shell->status);
			free(pars->token->value);
			pars->token->value = ft_strdup(status);
			free(status);
		}
		else
			pars->token->value = NULL;
		token_add_back(&pars->head, pars->token);
		pars->start = pars->count + 1;
	}
}

void	dollar_state_handler_quoted(char *stringa, t_parser *pars,
		t_shell *shell)
{
	dollar_state_handler_quoted_if_clause(stringa, pars, shell);
	if (pars->count > pars->start)
	{
		pars->token = token_new(NULL);
		pars->info = (t_token_info){DOLLAR_TOKEN, stringa, pars->start,
			pars->count};
		set_token_values(pars->token, &pars->info);
		if (pars->token->value)
		{
			expand_env_var(&pars->token, &pars->token->value, shell);
			if (pars->token && pars->token->value)
				token_add_back(&pars->head, pars->token);
		}
		else
		{
			free(pars->token);
			pars->token = NULL;
		}
		pars->start = pars->count;
		pars->count--;
	}
	pars->state = STATE_GENERAL;
}
