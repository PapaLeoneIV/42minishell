/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quot_tokenizer_utils2.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rileone <rileone@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/05 10:16:41 by rileone           #+#    #+#             */
/*   Updated: 2024/07/05 10:17:16 by rileone          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

int	valid_regchar_quoted(char c)
{
	char	*valid_char;
	int		len;
	int		i;

	i = 0;
	valid_char = "_";
	len = ft_strlen(valid_char);
	while (i < len)
	{
		if (ft_charchar(c, valid_char[i]))
			return (1);
		i++;
	}
	return (0);
}

int	get_char_type_quoted(char c)
{
	if (c == ' ')
		return (WHITESPACE_CHAR);
	else if (c == '$')
		return (DOLLAR_CHAR);
	else if (c == '?')
		return (QUESTION_MARK_CHAR);
	else if (ft_isalpha(c) || valid_regchar_quoted(c))
		return (REG_CHAR);
	else if (ft_isdigit(c))
		return (DIGIT_CHAR);
	return (DOLLAR_SPECIAL_CHAR);
}

void	init_parser_quot(t_parser *parser)
{
	parser->state = STATE_GENERAL;
	parser->start = 0;
	parser->count = 0;
	parser->head = NULL;
}

void	set_values(char *stringa, t_parser *pars, int type)
{
	pars->token = token_new(NULL);
	pars->info = (t_token_info){type, stringa, pars->start,
		pars->count + 1};
	set_token_values(pars->token, &pars->info);
}
