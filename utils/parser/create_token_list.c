/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_token_list.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rileone <rileone@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 14:36:02 by rileone           #+#    #+#             */
/*   Updated: 2024/05/05 14:52:55 by rileone          ###   ########.fr       */
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

int create_token_list(char *stringa, t_shell *shell)
{
	t_parser pars;
	
	pars = (t_parser){0};
	pars.state = STATE_GENERAL;
	if (stringa == NULL || shell == NULL)
		return (-1);
	while(stringa[pars.count] == ' ')  																//in bash non penso esistano backspace, tab, e altri
		pars.count++;
	pars.start = pars.count;
	while (stringa[pars.count] != '\0')
	{
		pars.char_type = get_char_type(stringa, &pars); 											// GET CHAR TYPE of the current char													
		if (pars.state == STATE_GENERAL)
			general_state_handler(stringa, &pars);  												//GENERAL STATE		
		else if ((pars.state == STATE_SQUOTE && pars.char_type == SQUOTES_CHAR) 
		|| (pars.state == STATE_DQUOTE && pars.char_type == DQUOTES_CHAR)) 							//QUOTE STATE                                                                                                        
			quoted_state_handler(stringa, &pars);
		else if (pars.state == STATE_DOLLAR && pars.char_type != REG_CHAR)
			dollar_state_handler(stringa, &pars, shell);											//DOLLAR STATE
		if (stringa[pars.count + 1] == '\0')
			slice_end_token(stringa, &pars, shell);														//SLICE END TOKEN						
		pars.count++;
	}
	(void)shell;
	token_print(pars.head);
	return (0);
}


/* 	transform_genwords_to_cmds(&pars.head, shell); */
/* void transform_genwords_to_cmds(t_token **head, t_shell *shell)
{
	t_token *ptr;
	int 	i;
	char 	**pathmtx;
	char *str;
	ptr = *head;
	i = 0;
	pathmtx = return_path_string_splitted(head, shell);
	while(ptr)
	{
		if (ptr->type == WORD_TOKEN)
		{
			i = 0;
			while(pathmtx && pathmtx[i])
			{
				str = ft_strjoin(pathmtx[i], ptr->value);		
				if (access(str, F_OK) == 0)
					ptr->type = CMD_TOKEN;
				i++;
				free(str);
			}	
		}
		ptr = ptr->next;
	}
} */