/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_state_methods.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rileone <rileone@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 15:32:43 by rileone           #+#    #+#             */
/*   Updated: 2024/05/17 14:56:07 by rileone          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "../../includes/lexer.h"

void quoted_state_handler(char *stringa, t_parser *pars)
{
	int Mquotes_arr[2] = {DOUBLE_QUOTES_TOKEN, SING_QUOTES_TOKEN};
	pars->token = token_new(NULL);
	pars->info = (t_token_info){Mquotes_arr[pars->char_type == SQUOTES_CHAR], stringa, pars->start + 1, pars->count};
	set_token_values(pars->token, &pars->info);
	token_add_back(&pars->head, pars->token);
	pars->start = pars->count + 1;
	pars->state = STATE_GENERAL;
}

void dollar_state_handler(char *stringa, t_parser *pars, t_shell *shell)
{
	/***qui dipende se voglio gestire $1 $2 $3 $? ....*/


	/***per il momento $? viene espanso e risulta uguale a NULL (ERRORE)*/
	if ((pars->count > pars->start && pars->char_type == DIGIT_CHAR && stringa[pars->count - 1] == '$') ||
	(pars->count > pars->start && pars->char_type == QUESTION_MARK_CHAR && stringa[pars->count - 1] == '$'))
	{
		pars->token = token_new(NULL);
		pars->info = (t_token_info){DOLLAR_TOKEN, stringa, pars->start, pars->count + 1};
		set_token_values(pars->token, &pars->info);
		if (strcmp(pars->token->value, "$0") == 0)
			pars->token->value = ft_strdup("bash");
		else
			pars->token->value = NULL;
		token_add_back(&pars->head, pars->token);
		pars->start = pars->count + 1;
	}
	if (pars->count > pars->start)
	{
		pars->token = token_new(NULL);
		pars->info = (t_token_info){DOLLAR_TOKEN, stringa, pars->start, pars->count}; 
		set_token_values(pars->token, &pars->info);
		if (pars->token->value)
		{
			token_add_back(&pars->head, pars->token);
			expand_env_var(&pars->token->value, shell);		
		}
		else
			free(pars->token);
		pars->start = pars->count;
		pars->count--;
	}
	
	pars->state = STATE_GENERAL;
}


void general_state_handler(char *stringa, t_parser *pars)
{
	char c;
	
	if (pars->char_type == WHITESPACE_CHAR || pars->char_type == PIPELINE_CHAR || pars->char_type == REDIR_INPUT_CHAR 
	|| pars->char_type ==  REDIR_OUTPUT_CHAR || pars->char_type == SQUOTES_CHAR || pars->char_type == DQUOTES_CHAR 
	|| pars->char_type == DOLLAR_CHAR)
	{	
		c = get_char_type(stringa, pars, pars->count + 1);
		if (pars->char_type == DOLLAR_CHAR && c == WHITESPACE_CHAR)
		{
			slice_token_string_doll_spec_case(stringa, pars);
			return ;
		}
		if (pars->count > pars->start)																								//se ho incontrato uno dei carattere nell if precedente posso tagliare la stringa
			slice_token_string(stringa, pars);
		if ((pars->char_type == REDIR_OUTPUT_CHAR && look_for_another_redirect(stringa, pars) == REDIR_OUTPUT_CHAR ) 
		|| ( pars->char_type == REDIR_INPUT_CHAR && look_for_another_redirect(stringa, pars) == REDIR_INPUT_CHAR))
			return (slice_redirect_token(stringa, pars));
		if (pars->char_type == REDIR_OUTPUT_CHAR || pars->char_type == REDIR_INPUT_CHAR 
		|| pars->char_type == PIPELINE_CHAR || pars->char_type == WHITESPACE_CHAR) 															//incotro un carattere speciale e me lo prendo
			slice_single_char_token(stringa, pars);
		if (pars->char_type == SQUOTES_CHAR || pars->char_type == DQUOTES_CHAR  || pars->char_type == DOLLAR_CHAR)  						//cambio lo state machine per gestire le virgolette
			check_and_change_status(&pars->state, pars->char_type, pars);
	}
}



