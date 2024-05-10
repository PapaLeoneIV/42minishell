/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_token_list.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rileone <rileone@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 14:36:02 by rileone           #+#    #+#             */
/*   Updated: 2024/05/06 19:06:09 by rileone          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/lexer.h"

/*TODO :
	- devo controllare che tutti i token vengono assegnati correttamente es :WHITESPACE not handle atm FATTO_
	- devo finire di parsere: devo trovare un modo di capire quando vanno incollati insieme due > > &&  < < FATTO
	- devo capire quando devo incollare insieme i dollar sign con le stringhe 
	precedenti e posteriori (mi sembra di doverle attaccare solo quando non c e il whitespace)
	- devo finire di espandere le variabili quando necessario
*/
int create_token_list(char *stringa, t_shell *shell, t_parser *pars)
{
	if (stringa == NULL || shell == NULL || pars == NULL)
		return (0);
	while(stringa[pars->count] == ' ')  																	//in bash non penso esistano backspace, tab, e altri
		pars->count++;
	pars->start = pars->count;
	while (stringa[pars->count] != '\0')
	{
		pars->char_type = get_char_type(stringa, pars); 												// GET CHAR TYPE of the current char													
		if (pars->state == STATE_GENERAL)	
			general_state_handler(stringa, pars);  													//GENERAL STATE		
		else if ((pars->state == STATE_SQUOTE && pars->char_type == SQUOTES_CHAR) 
		|| (pars->state == STATE_DQUOTE && pars->char_type == DQUOTES_CHAR)) 								//QUOTE STATE                                                                                                        
			quoted_state_handler(stringa, pars);
		else if (pars->state == STATE_DOLLAR && pars->char_type != REG_CHAR)
			dollar_state_handler(stringa, pars, shell);												//DOLLAR STATE
		if (stringa[pars->count + 1] == '\0')
			slice_end_token(stringa, pars, shell);														//SLICE END TOKEN						
		pars->count++;
	}
	(void)shell;
	return (1);
}

void trim_middleline_whitespaces(t_parser *pars)
{
	t_token *ptr;
	t_token *tmp;
	t_token *current;

	ptr = pars->head;
	while(ptr)
	{
		if (ptr && ptr->type == WHITESPACE_TOKEN)
		{
			tmp = ptr->next;
			while(tmp->type == WHITESPACE_TOKEN)
			{
				current = tmp;
				tmp = tmp->next;
				free(current); //devo liberare meglio tutto il token anche value credo 
			}
			ptr->next = tmp;
			tmp->prev = ptr;
		}
		ptr = ptr->next;
	}
}

void remove_null_tokens(t_parser *pars)
{
	t_token *ptr;
	t_token *tmp;

	ptr = pars->head;
	while(ptr)
	{
		if (ptr && ptr->value == NULL)
		{
			tmp = ptr;
			ptr->prev->next = ptr->next;
			if (ptr->next != NULL)
				ptr->next->prev = ptr->prev;
			free(tmp);
			tmp = NULL;
		}
		ptr = ptr->next;
	}
}

int tokenize_input(char *input, t_shell *shell)
{
	t_parser pars;

	pars = (t_parser){0};
	if (create_token_list(input, shell, &pars) == 0)
		return (0);
	unpack_quoted_tokens(&pars, shell);
	join_tokens_values_when_no_space_between(&pars, shell);
	trim_middleline_whitespaces(&pars);
	remove_null_tokens(&pars);
	token_print(pars.head);													//to use tester.py enable this function
	(void)shell;
	/* while(pars.head)
	{	
		printf("type: %d, ", pars.head->type);
		printf("value: %s\n", pars.head->value);
		pars.head = pars.head->next;
	} */ 
	return (0);
}
