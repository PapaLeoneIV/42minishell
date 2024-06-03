/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_slice_methods.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rileone <rileone@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 19:15:28 by rileone           #+#    #+#             */
/*   Updated: 2024/06/03 18:30:47 by rileone          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/lexer.h"

/*Funzione che serve per tagliare i vari token speciali composti da un solo carattere*/

char *expand_tilde(t_shell *shell)
{
	while(ft_strncmp(shell->env[0]->head,"HOME", 4))
		shell->env[0] = shell->env[0]->next; 
	return(ft_strdup(shell->env[0]->body));
}

void slice_single_char_token(char *stringa, t_parser *pars, t_shell *shell)
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
	else if (pars->char_type == TILDE_CHAR)
		pars->info = (t_token_info){WORD_TOKEN, stringa, pars->count, pars->count + 1};
	set_token_values(pars->token, &pars->info);
	if (!ft_strncmp(pars->token->value, "~", 1))
	{
		free(pars->token->value);
		pars->token->value = expand_tilde(shell);
	}
	token_add_back(&pars->head, pars->token);
	pars->start = pars->count + 1;
}

/**Caso limite dove il carattere "$" isolato viene gestito come una qualsiasi stringa*/

void slice_token_string_doll_spec_case(char *stringa, t_parser *pars)
{
	pars->token = token_new(NULL);
	pars->info = (t_token_info){WORD_TOKEN, stringa, pars->start, pars->count + 1};
	set_token_values(pars->token, &pars->info);
	token_add_back(&pars->head, pars->token);
	pars->start = pars->count + 1;

}



/**Funzione per tagliare i token nel GENERAL STATE*/

void slice_token_string(char *stringa, t_parser *pars)
{
	pars->token = token_new(NULL);
	pars->info = (t_token_info){WORD_TOKEN, stringa, pars->start, pars->count};
	set_token_values(pars->token, &pars->info);
	token_add_back(&pars->head, pars->token);
	pars->start = pars->count + 1;

}

/**Funzione per gestire la EOL, il token->type viene affidato in base allo STATE in cui 
 * la macchina si trova in quel momento.
*/

int slice_end_token(char *stringa, t_parser *pars, t_shell *shell)
{
	if (stringa[pars->count] == '\0')
		return 0;
	if (pars->state == STATE_DQUOTE)
		return(perror("Error: unclosed double quotes\n"), 0);
	else if (pars->state == STATE_SQUOTE)	
		return(perror("Error: unclosed single quotes\n"), 0);
	else if (pars->state == STATE_DOLLAR)
		pars->info = (t_token_info){DOLLAR_TOKEN, stringa, pars->start, pars->count + 1};
	else 
		pars->info = (t_token_info){WORD_TOKEN, stringa, pars->start, pars->count + 1};
	pars->token = token_new(NULL);
	set_token_values(pars->token, &pars->info);
 	if (pars->token->value && !ft_strncmp(pars->token->value, "~", ft_strlen(pars->token->value)))
	{
		free(pars->token->value);
		pars->token->value = expand_tilde(shell);
	}
	if (pars->token->type == WORD_TOKEN && !ft_strncmp(pars->token->value, "", ft_strlen(pars->token->value)))
	{
	 	free(pars->token->value);
		free(pars->token); 
		return 1;
	}
	if (pars->token->type == DOLLAR_TOKEN && ft_strncmp(pars->token->value, "$", ft_strlen(pars->token->value)))
	{
		expand_env_var(&pars->token->value, shell);
		if(pars->token->value)
			token_add_back(&pars->head, pars->token);
		else
		{
			free(pars->token->value);
			free(pars->token);



			
		}
	}
	else
		token_add_back(&pars->head, pars->token);
	return (SUCCESS);
}

/**Caso limite dove controllo il carattere corrente e quello successivo per vedere
 * se si tratte di una singola o doppia redirection.
*/

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