/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_state_methods.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rileone <rileone@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 15:32:43 by rileone           #+#    #+#             */
/*   Updated: 2024/05/21 20:06:00 by rileone          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "../../includes/lexer.h"

/*Funzione per la gestione dello QUOTED STATE*/
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

/*Funzione per la gestione del DOLLAR STATE*/

void dollar_state_handler(char *stringa, t_parser *pars, t_shell *shell)
{
	/**TODO, $? viene espanso a NULL*/
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


/*Funzione per la gestione dello GENERAL STATE*/

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
		if (pars->count > pars->start)
			slice_token_string(stringa, pars);
		if ((pars->char_type == REDIR_OUTPUT_CHAR && look_for_another_redirect(stringa, pars) == REDIR_OUTPUT_CHAR ) 
		|| ( pars->char_type == REDIR_INPUT_CHAR && look_for_another_redirect(stringa, pars) == REDIR_INPUT_CHAR))
			return (slice_redirect_token(stringa, pars));
		if (pars->char_type == REDIR_OUTPUT_CHAR || pars->char_type == REDIR_INPUT_CHAR 
		|| pars->char_type == PIPELINE_CHAR || pars->char_type == WHITESPACE_CHAR) 															
			slice_single_char_token(stringa, pars);
		if (pars->char_type == SQUOTES_CHAR || pars->char_type == DQUOTES_CHAR  || pars->char_type == DOLLAR_CHAR) 
			check_and_change_status(&pars->state, pars->char_type, pars);
	}
}



