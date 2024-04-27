/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_token_list.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rileone <rileone@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 14:36:02 by rileone           #+#    #+#             */
/*   Updated: 2024/04/27 11:24:06 by rileone          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/lexer.h"
#include "lexer.h"




	int get_char(char carattere)
	{
		if (carattere == ' ')
			return (WHITESPACE);
		else if (carattere == '|')
			return (PIPELINE);
		else if (carattere == '<')
			return (REDIR_INPUT);
		else if (carattere == '>')
			return (REDIR_OUTPUT);
		else if (carattere == '\'')
			return (SQUOTES);
		else if (carattere == '\"')
			return (DQUOTES);
		else if (carattere == '$')
			return (DOLLAR_CHAR);
		return (REG_CHAR);
	}

	int create_token_list(char *stringa, t_shell *shell)
	{
		int state = STATE_GENERAL;
		t_token *head;
		t_token *token;
		t_token_info info;
		int c;
		int i;
		int start = 0;

		head = NULL;
		i = 0;
		if (stringa == NULL || shell == NULL)
			return (-1);
		while (stringa[i] != '\0')
		{
			c = get_char(stringa[i]); // prendo il CharType del carattere
			if (state == STATE_GENERAL)
			{
				if (c == REDIR_OUTPUT || c == PIPELINE || c == REDIR_INPUT //se non incontro un REG_CHAR posso creare un token
				|| c ==  WHITESPACE|| c == SQUOTES || c == DQUOTES || c == DOLLAR_CHAR)
				{
					if (i > start)  //se ho incontrato uno dei carattere nell if precedente posso tagliare la stringa
					{
						token = token_new(NULL);

						info = (t_token_info){WORD_TOKEN, stringa, start, i}; 
						set_token_values(token, &info);
						token_add_back(&head, token);
						start = i + 1; //sposto start alla fine del token
					}
					if (c == REDIR_OUTPUT || c == REDIR_INPUT || c == PIPELINE || c == WHITESPACE) //incotro un carattere speciale e me lo prendo
					{
						token = token_new(NULL);
						info = (t_token_info){WORD_TOKEN, stringa, i, i + 1};
						set_token_values(token, &info);
						token_add_back(&head, token);
						start = i + 1; //sposto start alla fine del token
					}
					if (c == SQUOTES || c == DQUOTES  || c == DOLLAR_CHAR)   //cambio lo state machine per gestire le virgolette
					{
						if (c == SQUOTES)
							state = STATE_SQUOTE;
						else if (c == DQUOTES)
							state = STATE_DQUOTE;
						else if (c == DOLLAR_CHAR)
							state = STATE_DOLLAR;
						start = i;    
					}
					
				}
			}
			else if ((c == SQUOTES && state == STATE_SQUOTE) || (c == DQUOTES && state == STATE_DQUOTE)) //VIRGOLETTE STATE: qui vengono le virgolette                                                                                                           
			{
				int Mquotes_arr[2] = {DOUBLE_QUOTES, SING_QUOTES};

				token = token_new(NULL);
				info = (t_token_info){Mquotes_arr[c == SQUOTES], stringa, start, i + 1};
				set_token_values(token, &info);
				token_add_back(&head, token);
				start = i + 1;
				state = STATE_GENERAL;   //resetto lo state machine
			}
			/**penso che qui devo distinguere in base ai vari casi, ovvero posso fare start piu uno solo se incontro lo spazio
			 * altrimenti devo prendere la stringa fino a i, e non spostare start 
			*/
			else if (state == STATE_DOLLAR && (c == DOLLAR_CHAR || c == WHITESPACE || c == DQUOTES || c == SQUOTES || c == REDIR_INPUT || c == REDIR_OUTPUT || c == PIPELINE))
			{
				if (i > start)
				{
					token = token_new(NULL);
					info = (t_token_info){DOLLAR_CHAR, stringa, start, i}; 
					set_token_values(token, &info);
					token_add_back(&head, token);
					start = i; //sposto start alla fine del token
					i--;
				}
				state = STATE_GENERAL;
			}
			if (stringa[i + 1] == '\0' && i > start)  //prendo l ultimo token
			{
				token = token_new(NULL);
				info = (t_token_info){WORD_TOKEN, stringa, start, i + 1};
				set_token_values(token, &info);
				token_add_back(&head, token);
			}
			i++;
		}
		(void)shell;
		// Print token values
		token = head;
		while (token != NULL) 
		{
			printf("%s\n", token->value);
			token = token->next;
		}
	return (0);
	}