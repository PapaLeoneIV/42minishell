/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgori <fgori@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 14:36:02 by rileone           #+#    #+#             */
/*   Updated: 2024/07/02 11:52:07 by fgori            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/lexer.h"

int	create_token_list(char *str, t_shell *shell, t_parser *pars)
{
	if (str == NULL || shell == NULL || pars == NULL)
		return (ERROR);
	while (str[pars->count] == ' ')
		pars->count++;
	pars->start = pars->count;
	while (str[pars->count] != '\0')
	{
		pars->char_type = get_char_type(str, pars, pars->count);
		if (pars->state == STATE_GENERAL)
			general_state_handler(str, pars, shell);
		else if ((pars->state == STATE_SQUOTE
				&& pars->char_type == SQUOTES_CHAR)
			|| (pars->state == STATE_DQUOTE
				&& pars->char_type == DQUOTES_CHAR))
			quoted_state_handler(str, pars);
		else if (pars->state == STATE_DOLLAR && ((pars->char_type != REG_CHAR
					&& pars->char_type != DIGIT_CHAR)
				|| (pars->char_type == DIGIT_CHAR && str[pars->count
						- 1] == '$')))
			dollar_state_handler(str, pars, shell);
		if (str[pars->count + 1] == '\0' && !slice_end_token(str, pars, shell))
			return (ERROR);
		pars->count++;
	}
	return (SUCCESS);
}

void	trim_middleline_whitespaces(t_parser *pars)
{
	t_token	*ptr;
	t_token	*tmp;
	t_token	*current;

	ptr = pars->head;
	while (ptr)
	{
		if (ptr && ptr->type == WHITESPACE_TOKEN)
		{
			tmp = ptr->next;
			while (tmp && tmp->type == WHITESPACE_TOKEN)
			{
				current = tmp;
				tmp = tmp->next;
				free(current->value);
				free(current);
			}
			ptr->next = tmp;
			if (tmp)
				tmp->prev = ptr;
		}
		ptr = ptr->next;
	}
}

t_token	*tokenize_input(char *input, t_shell *shell)
{
	t_parser	pars;
	t_token		*head;

	pars = (t_parser){0};
	if (create_token_list(input, shell, &pars) == ERROR)
		return (free_tokens(pars.head), NULL);
	unpack_quoted_tokens(&(pars.head), shell);
	join_tokens_values_when_no_space_between(&pars);
	trim_middleline_whitespaces(&pars);
	remove_null_tokens(&pars);
	head = pars.head;
	return (head);
}
