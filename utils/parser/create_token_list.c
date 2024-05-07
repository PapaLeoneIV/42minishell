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
/* int refine_token_list(char *stringa, t_shell **shell)
{
	
} */



/* int parse_redirection(char *input, t_shell *shell, t_parser *pars)
{
	t_token *ptr;
	t_command *command;
	int count;
	
	while(ptr != NULL)
	{
		command = ft_calloc(1 ,sizeof(t_command));
		command = (t_command *){0};
		count = 0;
		while(ptr->type != PIPE_TOKEN || ptr == NULL)
		{
			if (ptr->type == WHITESPACE_TOKEN)
				continue;
			if (ptr->type == WORD_TOKEN && count == 0)
				ptr->type = CMD_TOKEN;
			il resto li inserisco dentro una matrice
			if (ptr->type == HEREDOC_TOKEN || ptr->type == REDIR_OUT_TOKEN 
			||ptr->type == GREATER_TOKEN || ptr->type == LESSER_TOKEN)
			{
				//handle_redirection(ptr, pars);
			}
			solo le redirection devo salvare come informazione particolare
			ptr = ptr->next;
			count++;
		}
		quando esco dal loop interno sono arrivato alla pip
	}
	
}
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

t_token *check_prev(t_token *token)
{
	t_token *prev;

	prev = token->prev;
	if (prev == NULL || prev->type == WHITESPACE_TOKEN)
		return NULL;
	if (prev->type == WORD_TOKEN || prev->type == DOUBLE_QUOTES_TOKEN
	|| prev->type == SING_QUOTES_TOKEN || prev->type == DOLLAR_TOKEN)
		return prev; 
	return NULL;
}

void join_tokens(t_token **node, t_token **prev)
{
	(*prev)->value = ft_strjoin((*prev)->value, (*node)->value);
	if((*node)->next)
		(*node)->next->prev = (*prev);
	else
		(*prev)->next = NULL;
	(*prev)->next = (*node)->next;
	free((*node)->value);
	free(*node);
	*node = NULL;
	*node = *prev;
}

void join_string(t_parser *pars, t_shell *shell)
{
	int i;
	t_token *prev;
	t_token *ptr;
	(void)shell;
	i = 0;
	ptr = pars->head;
	while(ptr != NULL)
	{
		prev = check_prev(ptr);
		if (!prev)
		{
			ptr = ptr->next;
			continue;
		}
		if (ptr && (ptr->type == WORD_TOKEN || ptr->type == SING_QUOTES_TOKEN 
		|| ptr->type == DOUBLE_QUOTES_TOKEN || ptr->type == DOLLAR_TOKEN ) && prev)
			join_tokens(&ptr, &prev);
		ptr = ptr->next;
	}
}

void unpack_quoted_tokens(t_parser *pars)
{
	
}

int parse_input(char *input, t_shell *shell)
{
	t_parser pars;

	pars = (t_parser){0};
	if (create_token_list(input, shell, &pars) == 0)
		return (0);
 	join_string(&pars, shell);
	unpack_quoted_tokens(&pars);
	token_print(pars.head);
	(void)shell;
    /*parse_redirections(input, shell, &pars);*/
	return (0);
}
