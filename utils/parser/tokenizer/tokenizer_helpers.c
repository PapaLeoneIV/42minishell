/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_helpers.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rileone <rileone@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/28 19:16:34 by rileone           #+#    #+#             */
/*   Updated: 2024/06/01 14:21:05 by rileone          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/lexer.h"

/**I caratteri contenuti nella variabile valid_char 
 * sono gli unici caratteri oltre alle lettere dell alfabeto
 * che possono essere parte di token WORD_TOKEN ( piu semplicemente 
 * file, nomi di variabili, env ...)
*/

int valid_regchar(char *str, t_parser *pars)
{
	char *valid_char;
	int len;
	int i;

	i = 0;
	valid_char = "_";
	len = ft_strlen(valid_char);
	while(i < len)
	{
		if(ft_charchar(str[pars->count], valid_char[i]))
			return (1);
		i++;
	}
	return (0);
}

/**Una volta trovato un carattere che puo essere una redirection controllo
 * il carattere successivo per vedere se si tratta di una doppia redirection
 * 
*/

int look_for_another_redirect(char *stringa, t_parser *pars)
{
	if (stringa[pars->count + 1] == '>')
		return (REDIR_OUTPUT_CHAR);
	else if (stringa[pars->count + 1] == '<')
		return (REDIR_INPUT_CHAR);
	else
		return (-1);
}

/**Ogni carattere della stringa viene associato ad un carattere specifico, 
 * ovviamente i caratteri speciali hanno il loro CHAR, mentre lettere e 
 * numeri sono inseriti in un char piu generico 
*/

int get_char_type(char *str, t_parser *pars, int count)
{
	if (str[count] == ' ')
		return (WHITESPACE_CHAR);
	else if (str[count] == '|')
		return (PIPELINE_CHAR);
	else if (str[count] == '<')
		return (REDIR_INPUT_CHAR);
	else if (str[count] == '>')
		return (REDIR_OUTPUT_CHAR);
	else if (str[count] == '\'')
		return (SQUOTES_CHAR);
	else if (str[count] == '\"')
		return (DQUOTES_CHAR);
	else if (str[count] == '$')
		return (DOLLAR_CHAR);
	else if (str[count] == '?')
		return (QUESTION_MARK_CHAR);
	else if (str[count] == '~')
		return (TILDE_CHAR);
	else if (ft_isalpha(str[count]) || valid_regchar(str, pars))
		return (REG_CHAR);
	else if (ft_isdigit(str[count]))
		return (DIGIT_CHAR);
	return (DOLLAR_SPECIAL_CHAR);
}
/**Funzione inserita all interno del funzione che gestisce il 
 * lo state generale. Serve per cambiare lo STATE della machine.
*/

void check_and_change_status(int *state, int c, t_parser *pars)
{
	if (c == SQUOTES_CHAR)
		*state = STATE_SQUOTE;
	else if (c == DQUOTES_CHAR)
		*state = STATE_DQUOTE;
	else if (c == DOLLAR_CHAR)
		*state = STATE_DOLLAR;
	
	pars->start = pars->count; 
}
