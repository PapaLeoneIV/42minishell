/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_slice_methods.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rileone <rileone@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 19:15:28 by rileone           #+#    #+#             */
/*   Updated: 2024/05/14 14:42:18 by rileone          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/lexer.h"


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
void slice_token_string_doll_spec_case(char *stringa, t_parser *pars)
{
	pars->token = token_new(NULL);
	pars->info = (t_token_info){WORD_TOKEN, stringa, pars->start, pars->count + 1};
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

void slice_end_token(char *stringa, t_parser *pars, t_shell *shell)
{
	if (stringa[pars->start] == '\0')
		return ;
	pars->token = token_new(NULL);
	if (pars->state == STATE_DQUOTE)	
		pars->info = (t_token_info){DOUBLE_QUOTES_TOKEN, stringa, pars->start, pars->count + 1};
	else if (pars->state == STATE_SQUOTE)	
		pars->info = (t_token_info){SING_QUOTES_TOKEN, stringa, pars->start, pars->count + 1};
	else if (pars->state == STATE_DOLLAR)
		pars->info = (t_token_info){DOLLAR_TOKEN, stringa, pars->start, pars->count + 1};
	else
		pars->info = (t_token_info){WORD_TOKEN, stringa, pars->start, pars->count + 1};
	set_token_values(pars->token, &pars->info);
	if (pars->token->type == DOLLAR_TOKEN)
	{
		expand_env_var(&pars->token->value, shell);
		if(pars->token->value)
			token_add_back(&pars->head, pars->token);
		else
			free(pars->token);
	}
	else
		token_add_back(&pars->head, pars->token);
}

void slice_redirect_token(char *stringa, t_parser *pars)
{
	pars->token = token_new(NULL);
	if (stringa[pars->count + 1] == '<')
		pars->info = (t_token_info){HEREDOC_TOKEN, stringa, pars->count,pars->count + 2};
	else
		pars->info = (t_token_info){REDIR_OUT_TOKEN, stringa, pars->count,pars->count + 2};
	set_token_values(pars->token, &pars->info);
	token_add_back(&pars->head, pars->token);
	pars->start = pars->count + 2;
	pars->count++;
}