/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_slice_methods.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rileone <rileone@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 19:15:28 by rileone           #+#    #+#             */
/*   Updated: 2024/07/04 13:22:42 by rileone          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/lexer.h"

char	*expand_tilde(t_shell *shell)
{
	while (ft_strncmp(shell->env[0]->head, "HOME", 4))
		shell->env[0] = shell->env[0]->next;
	return (ft_strdup(shell->env[0]->body));
}

void	slice_single_char_token(char *stringa, t_parser *pars, t_shell *shell)
{
	pars->token = token_new(NULL);
	if (pars->char_type == PIPELINE_CHAR)
		pars->info = (t_token_info){PIPE_TOKEN, stringa, pars->count,
			pars->count + 1};
	else if (pars->char_type == REDIR_INPUT_CHAR)
		pars->info = (t_token_info){LESSER_TOKEN, stringa, pars->count,
			pars->count + 1};
	else if (pars->char_type == REDIR_OUTPUT_CHAR)
		pars->info = (t_token_info){GREATER_TOKEN, stringa, pars->count,
			pars->count + 1};
	else if (pars->char_type == WHITESPACE_CHAR)
		pars->info = (t_token_info){WHITESPACE_TOKEN, stringa, pars->count,
			pars->count + 1};
	else if (pars->char_type == TILDE_CHAR)
		pars->info = (t_token_info){WORD_TOKEN, stringa, pars->count,
			pars->count + 1};
	set_token_values(pars->token, &pars->info);
	if (!ft_strncmp(pars->token->value, "~", 1))
	{
		free(pars->token->value);
		pars->token->value = expand_tilde(shell);
	}
	token_add_back(&pars->head, pars->token);
	pars->start = pars->count + 1;
}

void	slice_token_string_doll_spec_case(char *stringa, t_parser *pars)
{
	pars->token = token_new(NULL);
	pars->info = (t_token_info){WORD_TOKEN, stringa, pars->start, pars->count
		+ 1};
	set_token_values(pars->token, &pars->info);
	token_add_back(&pars->head, pars->token);
	pars->start = pars->count + 1;
}

/**Funzione per tagliare i token nel GENERAL STATE*/

void	slice_token_string(char *stringa, t_parser *pars)
{
	pars->token = token_new(NULL);
	pars->info = (t_token_info){WORD_TOKEN, stringa, pars->start, pars->count};
	set_token_values(pars->token, &pars->info);
	token_add_back(&pars->head, pars->token);
	pars->start = pars->count + 1;
}

/**Funzione per gestire la EOL,
	il token->type viene affidato in base allo STATE in cui 
 * la macchina si trova in quel momento.
*/

int	set_token_info(t_token_info *info, t_parser *pars, char *stringa)
{
	if (stringa[pars->count] == '\0')
		return (0);
	if (pars->state == STATE_DQUOTE)
		return (perror("Error: unclosed double quotes\n"), ERROR);
	else if (pars->state == STATE_SQUOTE)
		return (perror("Error: unclosed single quotes\n"), ERROR);
	else if (pars->state == STATE_DOLLAR)
		*info = (t_token_info){DOLLAR_TOKEN, stringa,
			pars->start, pars->count + 1};
	else
		*info = (t_token_info){WORD_TOKEN, stringa,
			pars->start, pars->count + 1};
	return (SUCCESS);
}

void	fnfn(t_parser *pars, t_shell *shell)
{
	expand_env_var(&pars->token, &pars->token->value, shell);
	if (pars->token && pars->token->value)
		token_add_back(&pars->head, pars->token);
	else
	{
		if (pars->token)
			free(pars->token->value);
		free(pars->token);
	}
}

int	slice_end_token(char *stringa, t_parser *pars, t_shell *shell)
{
	if (set_token_info(&pars->info, pars, stringa) == ERROR)
		return (ERROR);
	pars->token = token_new(NULL);
	set_token_values(pars->token, &pars->info);
	if (pars->token->value && !ft_strncmp(pars->token->value, "~",
			ft_strlen(pars->token->value)))
	{
		free(pars->token->value);
		pars->token->value = expand_tilde(shell);
	}
	if (pars->token->type == WORD_TOKEN && !ft_strncmp(pars->token->value, "",
			ft_strlen(pars->token->value)))
		return (free(pars->token->value), free(pars->token), SUCCESS);
	if (pars->token->type == DOLLAR_TOKEN && ft_strncmp(pars->token->value, "$",
			ft_strlen(pars->token->value)))
		fnfn(pars, shell);
	else
		token_add_back(&pars->head, pars->token);
	return (SUCCESS);
}

void	slice_redirect_token(char *stringa, t_parser *pars)
{
	pars->token = token_new(NULL);
	if (stringa[pars->count + 1] == '<')
		pars->info = (t_token_info){HEREDOC_TOKEN, stringa, pars->count,
			pars->count + 2};
	else
		pars->info = (t_token_info){REDIR_OUT_TOKEN, stringa, pars->count,
			pars->count + 2};
	set_token_values(pars->token, &pars->info);
	token_add_back(&pars->head, pars->token);
	pars->start = pars->count + 2;
	pars->count++;
}
