/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_helpers.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rileone <rileone@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/28 19:16:34 by rileone           #+#    #+#             */
/*   Updated: 2024/04/30 17:44:16 by rileone          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/lexer.h"

int get_char_type(char *str, t_parser *pars)
{
	if (str[pars->count] == ' ')
		return (WHITESPACE_CHAR);
	else if (str[pars->count] == '|')
		return (PIPELINE_CHAR);
	else if (str[pars->count] == '<')
		return (REDIR_INPUT_CHAR);
	else if (str[pars->count] == '>')
		return (REDIR_OUTPUT_CHAR);
	else if (str[pars->count] == '\'')
		return (SQUOTES_CHAR);
	else if (str[pars->count] == '\"')
		return (DQUOTES_CHAR);
	else if (str[pars->count] == '$')
		return (DOLLAR_CHAR);
	else if (str[pars->count] == '?')
		return (QUESTION_MARK_CHAR);
	else if (ft_isalpha(str[pars->count]))
		return (REG_CHAR);
	else if (ft_isdigit(str[pars->count]))
		return (DIGIT_CHAR);
	return (DOLLAR_SPECIAL_CHAR);
}

void slice_single_char_token(char *stringa, t_parser *pars)
{
	pars->token = token_new(NULL);
	if (pars->char_type == PIPELINE_CHAR)
		pars->info = (t_token_info){PIPE_TOKEN, stringa, pars->count,pars->count + 1};
	else if (pars->char_type == REDIR_INPUT_CHAR)
		pars->info = (t_token_info){LESSER_TOKEN, stringa, pars->count, pars->count + 1};
	else if (pars->char_type == REDIR_OUTPUT_CHAR)
		pars->info = (t_token_info){GREATER_TOKEN, stringa, pars->count, pars->count + 1};
	else if (pars->char_type == WHITESPACE_CHAR)
		pars->info = (t_token_info){WHITESPACE_TOKEN, stringa, pars->count, pars->count + 1};
	set_token_values(pars->token, &pars->info);
	token_add_back(&pars->head, pars->token);
	pars->start = pars->count + 1;
}

void slice_token_string(char *stringa, t_parser *pars)
{
	pars->token = token_new(NULL);
	pars->info = (t_token_info){WORD_TOKEN, stringa, pars->start, pars->count};
	set_token_values(pars->token, &pars->info);
	token_add_back(&pars->head, pars->token);
	pars->start = pars->count + 1;

}

void slice_end_token(char *stringa, t_parser *pars)
{
	pars->token = token_new(NULL);
	pars->info = (t_token_info){WORD_TOKEN, stringa, pars->start, pars->count + 1};
	set_token_values(pars->token, &pars->info);
	token_add_back(&pars->head, pars->token);
}

void check_and_change_status(int *state, int c, t_parser *pars)
{
	if (c == SQUOTES_CHAR)
		*state = STATE_SQUOTE;
	else if (c == DQUOTES_CHAR)
		*state = STATE_DQUOTE;
	else if (c == DOLLAR_CHAR)
		*state = STATE_DOLLAR;
	pars->start = pars->count; 
}
