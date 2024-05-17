/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rileone <rileone@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 14:36:02 by rileone           #+#    #+#             */
/*   Updated: 2024/05/17 17:12:35 by rileone          ###   ########.fr       */
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


void print_token_type_and_value(t_token *head)
{
	t_token *current = head;
	while (current != NULL) {
			if (current->type == WORD_TOKEN) {
				printf("WORD_TOKEN ");
				// Handle WORD_TOKEN
			} else if (current->type == PIPE_TOKEN) {
				printf("PIPE_TOKEN ");
				// Handle PIPE_TOKEN
			} else if (current->type == GREATER_TOKEN) {
				printf("GREATER_TOKEN ");
				// Handle GREATER_TOKEN
			} else if (current->type == REDIR_OUT_TOKEN) {
				printf("REDIR_OUT_TOKEN ");
				// Handle REDIR_OUT_TOKEN
			} else if (current->type == LESSER_TOKEN) {
				printf("LESSER_TOKEN ");
				// Handle LESSER_TOKEN
			} else if (current->type == HEREDOC_TOKEN) {
				printf("HEREDOC_TOKEN ");
				// Handle HEREDOC_TOKEN
			} else if (current->type == SING_QUOTES_TOKEN) {
				printf("SING_QUOTES_TOKEN ");
				// Handle SING_QUOTES_TOKEN
			} else if (current->type == DOUBLE_QUOTES_TOKEN) {
				printf("DOUBLE_QUOTES_TOKEN ");
				// Handle DOUBLE_QUOTES_TOKEN
			} else if (current->type == DOLLAR_TOKEN) {
				printf("DOLLAR_TOKEN ");
				// Handle DOLLAR_TOKEN
			} else if (current->type == WHITESPACE_TOKEN) {
				printf("WHITESPACE_TOKEN ");
				// Handle WHITESPACE_TOKEN
			}
			printf("{Value: %s}\n", current->value);
			current = current->next;
		}
}

int create_token_list(char *stringa, t_shell *shell, t_parser *pars)
{
	if (stringa == NULL || shell == NULL || pars == NULL)
		return (0);
	while(stringa[pars->count] == ' ')  											
		pars->count++;
	pars->start = pars->count;
	while (stringa[pars->count] != '\0')
	{
		pars->char_type = get_char_type(stringa, pars, pars->count); 												
		if (pars->state == STATE_GENERAL)	
			general_state_handler(stringa, pars);  														
		else if ((pars->state == STATE_SQUOTE && pars->char_type == SQUOTES_CHAR) 
		|| (pars->state == STATE_DQUOTE && pars->char_type == DQUOTES_CHAR)) 							                                                                                                       
			quoted_state_handler(stringa, pars);
		else if (pars->state == STATE_DOLLAR && ((pars->char_type != REG_CHAR && pars->char_type != DIGIT_CHAR)
		|| (pars->char_type == DIGIT_CHAR && stringa[pars->count - 1] == '$')))
			dollar_state_handler(stringa, pars, shell);										
		if (stringa[pars->count + 1] == '\0')
		{
			if (!slice_end_token(stringa, pars, shell))
				return (0);																			
		}
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
			while(tmp && tmp->type == WHITESPACE_TOKEN)
			{
				current = tmp;
				tmp = tmp->next;
				free(current); //devo liberare meglio tutto il token anche value credo 
			}
			ptr->next = tmp;
			if (tmp)
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
		if (ptr == NULL)
			break;
		if (ptr && ptr->value == NULL)
		{
			tmp = ptr;
			if (ptr->prev != NULL)
				ptr->prev->next = ptr->next;
			if (ptr->next != NULL)
				ptr->next->prev = ptr->prev;
			free(tmp);
			tmp = NULL;
		}
		ptr = ptr->next;
	}
}

void change_non_special_tokens_to_word_tokens(t_parser *pars)
{
	t_token *ptr;

	ptr = pars->head;
	while(ptr)
	{
		if (ptr->type == DOLLAR_TOKEN 
		|| ptr->type == SING_QUOTES_TOKEN 
		|| ptr->type == DOUBLE_QUOTES_TOKEN) 
			ptr->type = WORD_TOKEN;
		ptr = ptr->next;
	}
	
}
void free_tokens(t_token *head)
{
	t_token *current;
	t_token *tmp;

	current = head;
	while (current != NULL)
	{
		tmp = current;
		current = current->next;
		free(tmp->value);
		free(tmp);
	}
}

t_token *tokenize_input(char *input, t_shell *shell)
{
	t_parser pars;
	t_token *head;

	pars = (t_parser){0};
	if (create_token_list(input, shell, &pars) == 0)
		return (free_tokens(pars.head), NULL);
	 unpack_quoted_tokens(&pars, shell);
	join_tokens_values_when_no_space_between(&pars, shell);
	trim_middleline_whitespaces(&pars);
	remove_null_tokens(&pars);
	//change_non_special_tokens_to_word_tokens(&pars);
 	token_print(pars.head);								//to use tester.py enable this function
 	//print_token_type_and_value(pars.head);  
	head = pars.head;
	return (head);
}