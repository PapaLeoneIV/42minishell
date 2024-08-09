/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_state_methods.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgori <fgori@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 15:32:43 by rileone           #+#    #+#             */
/*   Updated: 2024/07/16 12:31:42 by fgori            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "minishell.h"

t_token	*get_last_token(t_token *ptr)
{
	if (!ptr)
		return (NULL);
	while (ptr->next)
	{
		ptr = ptr->next;
	}
	return (ptr);
}

void	quoted_state_handler(char *stringa, t_parser *pars)
{
	int	here_doc_before;

	here_doc_before = look_behind_for_heredoc(pars->head);
	pars->token = token_new(NULL);
	if (here_doc_before == true)
		pars->info = (t_token_info){HERDOC_FILENAME_WITHQUOTES, stringa,
			pars->start + 1, pars->count};
	else
		pars->info = (t_token_info){(int [2]){DOUBLE_QUOTES_TOKEN,
			SING_QUOTES_TOKEN}[pars->char_type == SQUOTES_CHAR],
			stringa, pars->start + 1, pars->count};
	set_token_values(pars->token, &pars->info);
	token_add_back(&pars->head, pars->token);
	pars->start = pars->count + 1;
	pars->state = STATE_GENERAL;
}

void	fnfnfn(t_parser *pars, t_shell *shell, int type, char *stringa)
{
	pars->token = token_new(NULL);
	pars->info = (t_token_info){type, stringa, pars->start,
		pars->count};
	set_token_values(pars->token, &pars->info);
	if (pars->token->value)
	{
		expand_env_var(&pars->token, &pars->token->value, shell);
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

void	dollar_state_handler(char *stringa, t_parser *pars, t_shell *shell)
{
	if (pars->count > pars->start && pars->char_type == QUESTION_MARK_CHAR
		&& stringa[pars->count - 1] == '$')
	{
		pars->token = token_new(NULL);
		pars->info = (t_token_info){DOLLAR_TOKEN, stringa, pars->start,
			pars->count + 1};
		set_token_values(pars->token, &pars->info);
		handle_special_case(pars, shell);
	}
	if (pars->count > pars->start)
		fnfnfn(pars, shell, DOLLAR_TOKEN, stringa);
	pars->state = STATE_GENERAL;
}

void	general_state_handler(char *stringa, t_parser *pars)
{
	char	next;
	char	prev;

	prev = -1;
	next = -1;
	if (check_token(pars) == SUCCESS)
	{
		if (stringa[pars->count + 1])
			next = get_char_type(stringa, pars, pars->count + 1);
		if (pars->char_type == DOLLAR_CHAR && next == WHITESPACE_CHAR)
			return (slice_token_string_doll_spec_case(stringa, pars));
		if (pars->count > 0 && stringa[pars->count - 1])
			prev = get_char_type(stringa, pars, pars->count - 1);
		if (check_special_case_tilde(pars, prev, next) == SUCCESS)
			return (slice_single_char_token(stringa, pars));
		if (pars->count > pars->start && pars->char_type != TILDE_CHAR)
			slice_token_string(stringa, pars);
		if (check_redir_tokens(stringa, pars) == SUCCESS)
			return (slice_redirect_token(stringa, pars));
		if (check_single_tokens(pars) == SUCCESS)
			slice_single_char_token(stringa, pars);
		if (pars->char_type == SQUOTES_CHAR || pars->char_type == DQUOTES_CHAR
			|| pars->char_type == DOLLAR_CHAR)
			check_and_change_status(&pars->state, pars->char_type, pars);
	}
}
