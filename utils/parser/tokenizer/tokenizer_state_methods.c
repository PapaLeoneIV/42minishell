/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_state_methods.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rileone <rileone@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 15:32:43 by rileone           #+#    #+#             */
/*   Updated: 2024/06/27 17:47:43 by rileone          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/lexer.h"
#include "../../includes/minishell.h"

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

int	traverse_list_backword_for_heredoc(t_token *last_node)
{
	if (last_node->prev == NULL)
		return (false);
	while (last_node->type == WHITESPACE_TOKEN && last_node != NULL)
		last_node = last_node->prev;
	if (last_node->type == HEREDOC_TOKEN)
		return (true);
	else
		return (false);
}

int	look_behind_for_heredoc(t_token *head)
{
	t_token	*last;
	t_token	*ptr;

	ptr = head;
	last = get_last_token(ptr);
	if (!last)
		return (false);
	if (traverse_list_backword_for_heredoc(last))
		return (true);
	return (false);
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
		pars->info = (t_token_info){(int[2]){DOUBLE_QUOTES_TOKEN, SING_QUOTES_TOKEN}
			[pars->char_type == SQUOTES_CHAR], stringa, pars->start + 1, pars->count};
	set_token_values(pars->token, &pars->info);
	token_add_back(&pars->head, pars->token);
	pars->start = pars->count + 1;
	pars->state = STATE_GENERAL;
}

void	dollar_state_handler(char *stringa, t_parser *pars, t_shell *shell)
{
	char	*status;

	if ((pars->count > pars->start && pars->char_type == DIGIT_CHAR
			&& stringa[pars->count - 1] == '$') ||
		(pars->count > pars->start && pars->char_type == QUESTION_MARK_CHAR
				&& stringa[pars->count - 1] == '$'))
	{
		pars->token = token_new(NULL);
		pars->info = (t_token_info){DOLLAR_TOKEN, stringa, pars->start,
			pars->count + 1};
		set_token_values(pars->token, &pars->info);
		if (strcmp(pars->token->value, "$0") == 0)
		{
			free(pars->token->value);
			pars->token->value = ft_strdup("minishell");
		}
		else if (strcmp(pars->token->value, "$?") == 0)
		{
			status = ft_itoa(g_status_code);
			free(pars->token->value);
			pars->token->value = ft_strdup(status);
			free(status);
		}
		else
			pars->token->value = NULL;
		token_add_back(&pars->head, pars->token);
		pars->start = pars->count + 1;
	}
	if (pars->count > pars->start)
	{
		pars->token = token_new(NULL);
		pars->info = (t_token_info){DOLLAR_TOKEN, stringa, pars->start,
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
	pars->state = STATE_GENERAL;
}

void	general_state_handler(char *stringa, t_parser *pars, t_shell *shell)
{
	char	next;
	char	prev;

	prev = -1;
	next = -1;
	if (pars->char_type == WHITESPACE_CHAR || pars->char_type == PIPELINE_CHAR
		|| pars->char_type == REDIR_INPUT_CHAR
		|| pars->char_type == REDIR_OUTPUT_CHAR
		|| pars->char_type == SQUOTES_CHAR || pars->char_type == DQUOTES_CHAR
		|| pars->char_type == DOLLAR_CHAR || pars->char_type == TILDE_CHAR)
	{
		if (stringa[pars->count + 1])
			next = get_char_type(stringa, pars, pars->count + 1);
		if (pars->count > 0 && stringa[pars->count - 1])
			prev = get_char_type(stringa, pars, pars->count - 1);
		if (pars->char_type == DOLLAR_CHAR && next == WHITESPACE_CHAR)
		{
			slice_token_string_doll_spec_case(stringa, pars);
			return ;
		}
		if (pars->char_type == TILDE_CHAR && (prev == WHITESPACE_CHAR || !prev)
			&& next == WHITESPACE_CHAR)
		{
			return (slice_single_char_token(stringa, pars, shell));
		}
		if (pars->count > pars->start && pars->char_type != TILDE_CHAR)
			slice_token_string(stringa, pars);
		if ((pars->char_type == REDIR_OUTPUT_CHAR
				&& look_for_another_redirect(stringa,
					pars) == REDIR_OUTPUT_CHAR)
			|| (pars->char_type == REDIR_INPUT_CHAR
				&& look_for_another_redirect(stringa,
					pars) == REDIR_INPUT_CHAR))
			return (slice_redirect_token(stringa, pars));
		if (pars->char_type == REDIR_OUTPUT_CHAR
			|| pars->char_type == REDIR_INPUT_CHAR
			|| pars->char_type == PIPELINE_CHAR
			|| pars->char_type == WHITESPACE_CHAR)
			slice_single_char_token(stringa, pars, shell);
		if (pars->char_type == SQUOTES_CHAR || pars->char_type == DQUOTES_CHAR
			|| pars->char_type == DOLLAR_CHAR)
			check_and_change_status(&pars->state, pars->char_type, pars);
	}
}
