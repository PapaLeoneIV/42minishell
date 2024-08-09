/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_state_methods_help.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgori <fgori@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/05 10:22:32 by rileone           #+#    #+#             */
/*   Updated: 2024/07/16 12:31:11 by fgori            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "minishell.h"

void	handle_special_case(t_parser *pars, t_shell *shell)
{
	char	*status;

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

int	check_token(t_parser *pars)
{
	if (pars->char_type == WHITESPACE_CHAR || pars->char_type == PIPELINE_CHAR
		|| pars->char_type == REDIR_INPUT_CHAR
		|| pars->char_type == REDIR_OUTPUT_CHAR
		|| pars->char_type == SQUOTES_CHAR || pars->char_type == DQUOTES_CHAR
		|| pars->char_type == DOLLAR_CHAR || pars->char_type == TILDE_CHAR
	)
		return (SUCCESS);
	return (ERROR);
}

int	check_single_tokens(t_parser *pars)
{
	if ((pars->char_type == REDIR_OUTPUT_CHAR
			|| pars->char_type == REDIR_INPUT_CHAR
			|| pars->char_type == PIPELINE_CHAR
			|| pars->char_type == WHITESPACE_CHAR))
		return (SUCCESS);
	return (ERROR);
}

int	check_redir_tokens( char *stringa, t_parser *pars)
{
	if ((pars->char_type == REDIR_OUTPUT_CHAR
			&& look_for_another_redirect(stringa, pars) == REDIR_OUTPUT_CHAR)
		|| (pars->char_type == REDIR_INPUT_CHAR
			&& look_for_another_redirect(stringa, pars) == REDIR_INPUT_CHAR))
		return (SUCCESS);
	return (ERROR);
}

int	check_special_case_tilde(t_parser *pars, char prev, char next)
{
	if (pars->char_type == TILDE_CHAR && (prev == WHITESPACE_CHAR || !prev)
		&& next == WHITESPACE_CHAR)
		return (SUCCESS);
	return (ERROR);
}
