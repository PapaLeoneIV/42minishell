/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   state_handlers.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rileone <rileone@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 15:32:43 by rileone           #+#    #+#             */
/*   Updated: 2024/05/02 20:41:23 by rileone          ###   ########.fr       */
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


char *get_key_envp(char *envp_string)
{
	char *key;
	int end;

	end = ft_strchri_gnl(envp_string, '=');
	key = ft_substr(envp_string, 0, end);
	return (key);
}

void expand_env_var(char *token_value, t_parser *pars, t_shell *shell)
{
	int envp_len;
	int i;
	char *pathKey;
	
	i = 0;
	envp_len = mtx_count_rows(shell->envp);
	while(i < envp_len)
	{
		pathKey = get_key_envp(shell->envp[i]);
		if (!strcmp(token_value + 1, pathKey))
		{
			return shell->envp[i] + ft_strlen(ft_substring(shell->envp[i], ft_strchri_gnl(shell->envp[i], '='), ft_strlen(shell->envp[i])));
		}
		i++;
	}
	else
	{
		/**devo impostare il valore della variabile a NULL se non esiste*/
	}

}


void dollar_state_handler(char *stringa, t_parser *pars, t_shell *shell)
{
	/***qui dipende se voglio gestire $1 $2 $3 ....*/
	if ((pars->count > pars->start && pars->char_type == DIGIT_CHAR && stringa[pars->count - 1] == '$') ||
	(pars->count > pars->start && pars->char_type == QUESTION_MARK_CHAR && stringa[pars->count - 1] == '$'))
	{
		pars->token = token_new(NULL);
		pars->info = (t_token_info){DOLLAR_TOKEN, stringa, pars->start, pars->count + 1};
		set_token_values(pars->token, &pars->info);
		token_add_back(&pars->head, pars->token);
		pars->start = pars->count + 1;
	}
	if (pars->count > pars->start)
	{
		pars->token = token_new(NULL);
		pars->info = (t_token_info){DOLLAR_TOKEN, stringa, pars->start, pars->count}; 
		set_token_values(pars->token, &pars->info);
		token_add_back(&pars->head, pars->token);
		pars->start = pars->count;
		pars->count--;
	}
	expand_env_var(pars->token->value, pars, shell);
	pars->state = STATE_GENERAL;
}


void general_state_handler(char *stringa, t_parser *pars)
{
	if (pars->char_type == WHITESPACE_CHAR || pars->char_type == PIPELINE_CHAR || pars->char_type == REDIR_INPUT_CHAR 
	|| pars->char_type ==  REDIR_OUTPUT_CHAR || pars->char_type == SQUOTES_CHAR || pars->char_type == DQUOTES_CHAR 
	|| pars->char_type == DOLLAR_CHAR)
	{
		if (pars->count > pars->start)  																									//se ho incontrato uno dei carattere nell if precedente posso tagliare la stringa
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



