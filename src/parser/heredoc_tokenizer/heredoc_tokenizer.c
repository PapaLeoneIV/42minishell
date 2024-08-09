/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_tokenizer.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rileone <rileone@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 11:46:48 by fgori             #+#    #+#             */
/*   Updated: 2024/07/13 10:39:47 by rileone          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*heredoc_tokenizer(char *input, t_shell *shell)
{
	t_parser	pars;
	char		*output;

	pars = (t_parser){0};
	while (input[pars.count])
	{
		pars.char_type = get_char_type_heredoc(input, &pars, pars.count);
		if (pars.state == STATE_GENERAL)
			general_state_handler_heredoc(input, &pars);
		else if (pars.state == STATE_DOLLAR && ((pars.char_type != REG_CHAR
					&& pars.char_type != DIGIT_CHAR)
				|| (pars.char_type == DIGIT_CHAR && input[pars.count
						- 1] == '$')))
			dollar_state_handler(input, &pars, shell);
		if (input[pars.count + 1] == '\0' && !slice_end_token_heredoc(input,
				&pars, shell))
		{
			free_tokens(pars.head);
			return (NULL);
		}
		pars.count++;
	}
	output = join_token_values(pars.head);
	free_tokens(pars.head);
	return (output);
}
