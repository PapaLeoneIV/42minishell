/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_tokenizer_helpers.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rileone <rileone@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/05 10:04:32 by rileone           #+#    #+#             */
/*   Updated: 2024/07/13 10:38:40 by rileone          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	get_char_type_heredoc(char *str, t_parser *pars, int count)
{
	if (str[count] == ' ')
		return (WHITESPACE_CHAR);
	else if (str[count] == '$')
		return (DOLLAR_CHAR);
	else if (str[count] == '?')
		return (QUESTION_MARK_CHAR);
	else if (str[count] == '\n')
		return (NEWLINE_CHAR);
	else if (ft_isalpha(str[count]) || valid_regchar_heredoc(str, pars))
		return (REG_CHAR);
	else if (ft_isdigit(str[count]))
		return (DIGIT_CHAR);
	return (TERMINATOR_CHAR);
}

void	general_state_handler_heredoc(char *input,
	t_parser *pars)
{
	char	next;

	next = -1;
	if (pars->char_type == WHITESPACE_CHAR || pars->char_type == DOLLAR_CHAR
		|| pars->char_type == TERMINATOR_CHAR)
	{
		if (input[pars->count + 1])
			next = get_char_type(input, pars, pars->count + 1);
		if (pars->char_type == DOLLAR_CHAR && next == WHITESPACE_CHAR)
		{
			slice_token_string_doll_spec_case(input, pars);
			return ;
		}
		if (pars->count > pars->start)
			slice_token_string(input, pars);
		if (pars->char_type == WHITESPACE_CHAR)
			slice_single_char_token(input, pars);
		if (pars->char_type == SQUOTES_CHAR || pars->char_type == DQUOTES_CHAR
			|| pars->char_type == DOLLAR_CHAR)
			check_and_change_status(&pars->state, pars->char_type, pars);
	}
}

int	set_token_info_here(t_token_info *info, t_parser *pars, char *stringa)
{
	if (stringa[pars->count] == '\0')
		return (ERROR);
	else if (pars->state == STATE_DOLLAR)
		*info = (t_token_info){DOLLAR_TOKEN, stringa, pars->start,
			pars->count + 1};
	else
		*info = (t_token_info){WORD_TOKEN, stringa, pars->start,
			pars->count + 1};
	return (SUCCESS);
}

int	slice_end_token_heredoc(char *stringa,
	t_parser *pars, t_shell *shell)
{
	if (set_token_info_here(&pars->info, pars, stringa) == ERROR)
		return (ERROR);
	pars->token = token_new(NULL);
	set_token_values(pars->token, &pars->info);
	if (pars->token->type == WORD_TOKEN && !ft_strncmp(pars->token->value, "",
			ft_strlen(pars->token->value)))
		return (free(pars->token->value), free(pars->token), SUCCESS);
	if (pars->token->type == DOLLAR_TOKEN
		&& ft_strncmp(pars->token->value, "$",
			ft_strlen(pars->token->value)))
	{
		expand_env_var(&pars->token, &pars->token->value, shell);
		if (pars->token && pars->token->value)
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

char	*join_token_values(t_token *list)
{
	char	*output;
	char	*new_output;
	t_token	*ptr;

	output = NULL;
	ptr = list;
	while (ptr != NULL)
	{
		new_output = ft_strjoin(output, ptr->value);
		free(output);
		output = new_output;
		ptr = ptr->next;
	}
	return (output);
}
