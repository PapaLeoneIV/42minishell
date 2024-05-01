/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_token_list.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rileone <rileone@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 14:36:02 by rileone           #+#    #+#             */
/*   Updated: 2024/05/01 19:18:00 by rileone          ###   ########.fr       */
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
/**per distinguere fra comandi e parole random/argomenti posso passare il token attraverso la 
 * funzione access(), per controllare che sia effettivamente un comando FATTO
 * -----------------------
 * 
*/

void quoted_state_handler(char *stringa, t_parser *pars)
{
	int Mquotes_arr[2] = {DOUBLE_QUOTES_TOKEN, SING_QUOTES_TOKEN};
	pars->token = token_new(NULL);
	pars->info = (t_token_info){Mquotes_arr[pars->char_type == SQUOTES_CHAR], stringa, pars->start, pars->count + 1};
	set_token_values(pars->token, &pars->info);
	token_add_back(&pars->head, pars->token);
	pars->start = pars->count + 1;
	pars->state = STATE_GENERAL;
}




void dollar_state_handler(char *stringa, t_parser *pars)
{
	if ((pars->count > pars->start && pars->char_type == DIGIT_CHAR && stringa[pars->count - 1] == '$') ||
	(pars->count > pars->start && pars->char_type == QUESTION_MARK_CHAR && stringa[pars->count - 1] == '$'))
	{
		pars->token = token_new(NULL);
		pars->info = (t_token_info){DOLLAR_TOKEN, stringa, pars->start, pars->count + 1};
		set_token_values(pars->token, &pars->info);
		token_add_back(&pars->head, pars->token);
		pars->start = pars->count + 1;
	}
	if (pars->count > pars->start)
	{
		pars->token = token_new(NULL);
		pars->info = (t_token_info){DOLLAR_TOKEN, stringa, pars->start, pars->count}; 
		set_token_values(pars->token, &pars->info);
		token_add_back(&pars->head, pars->token);
		pars->start = pars->count;
		pars->count--;
	}
	pars->state = STATE_GENERAL;
}

int look_for_another_redirect(char *stringa, t_parser *pars)
{
	if (stringa[pars->count + 1] == '>')
		return (REDIR_OUTPUT_CHAR);
	else if (stringa[pars->count + 1] == '<')
		return (REDIR_INPUT_CHAR);
	else
		return (0);
}

void general_state_handler(char *stringa, t_parser *pars)
{
	if (pars->char_type == WHITESPACE_CHAR || pars->char_type == PIPELINE_CHAR || pars->char_type == REDIR_INPUT_CHAR 
	|| pars->char_type ==  REDIR_OUTPUT_CHAR || pars->char_type == SQUOTES_CHAR || pars->char_type == DQUOTES_CHAR 
	|| pars->char_type == DOLLAR_CHAR)
	{
		
		if (pars->count > pars->start)  //se ho incontrato uno dei carattere nell if precedente posso tagliare la stringa
			slice_token_string(stringa, pars);
		if ((pars->char_type == REDIR_OUTPUT_CHAR && look_for_another_redirect(stringa, pars) == REDIR_OUTPUT_CHAR ) 
		|| ( pars->char_type == REDIR_INPUT_CHAR && look_for_another_redirect(stringa, pars) == REDIR_INPUT_CHAR))
			return (slice_redirect_token(stringa, pars));
		if (pars->char_type == REDIR_OUTPUT_CHAR || pars->char_type == REDIR_INPUT_CHAR 
		|| pars->char_type == PIPELINE_CHAR || pars->char_type == WHITESPACE_CHAR) //incotro un carattere speciale e me lo prendo
			slice_single_char_token(stringa, pars);
		if (pars->char_type == SQUOTES_CHAR || pars->char_type == DQUOTES_CHAR  || pars->char_type == DOLLAR_CHAR)   //cambio lo state machine per gestire le virgolette
			check_and_change_status(&pars->state, pars->char_type, pars);
	}
}

char *path_string(t_shell *shell)
{
	int	i;

	i = 0;
	while (shell->envp[i])
	{
		if (ft_strncmp(shell->envp[i], "PATH=", 5) == 0)
			return (shell->envp[i] + 5);
		i++;
	}
	return (NULL);
}



char **return_path_string(t_token **head, t_shell *shell)
{
	char 	*tmpcmd;
	char	**tmpmtx;
	int		i;
	(void)head;
	i = 0;
	tmpcmd = path_string(shell);
	if (!tmpcmd)
		return NULL;
	tmpmtx = ft_split(tmpcmd, ':');
	while(tmpmtx && tmpmtx[i])
	{
		tmpmtx[i] = ft_strjoinchar(tmpmtx[i], '/');
		i++;
	}
	return (tmpmtx);
}

void transform_genwords_to_cmds(t_token **head, t_shell *shell)
{
	t_token *ptr;
	int 	i;
	char 	**pathmtx;
	char *str;
	ptr = *head;
	i = 0;
	pathmtx = return_path_string(head, shell);
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
}

int create_token_list(char *stringa, t_shell *shell)
{
	t_parser pars;
	
	pars = (t_parser){0};
	pars.state = STATE_GENERAL;
	if (stringa == NULL || shell == NULL)
		return (-1);
	while (stringa[pars.count] != '\0')
	{
		pars.char_type = get_char_type(stringa, &pars); 											// GET CHAR TYPE of the current char													
		if (pars.state == STATE_GENERAL)
			general_state_handler(stringa, &pars);  												//GENERAL STATE		
		else if ((pars.state == STATE_SQUOTE && pars.char_type == SQUOTES_CHAR) 
		|| (pars.state == STATE_DQUOTE && pars.char_type == DQUOTES_CHAR)) 							//QUOTE STATE                                                                                                        
			quoted_state_handler(stringa, &pars);
		else if (pars.state == STATE_DOLLAR && pars.char_type != REG_CHAR)
			dollar_state_handler(stringa, &pars);													//DOLLAR STATE
		if (stringa[pars.count + 1] == '\0')  														
			slice_end_token(stringa, &pars);														//SLICE END TOKEN						
		pars.count++;
	}
	transform_genwords_to_cmds(&pars.head, shell);
	





	
	(void)shell;
	// Print token values
	pars.token = pars.head;
	while (pars.token != NULL) 
	{
		printf("token type %i, value : %s  \n",pars.token->type, pars.token->value);
		pars.token = pars.token->next;
	}
	return (0);
}