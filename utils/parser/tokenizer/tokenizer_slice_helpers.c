/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_slice_helpers.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rileone <rileone@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/05 10:10:54 by rileone           #+#    #+#             */
/*   Updated: 2024/07/13 10:41:21 by rileone          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/lexer.h"

void	add_helper(t_parser *pars, t_shell *shell)
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
