/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_input.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rileone <rileone@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/21 17:12:07 by rileone           #+#    #+#             */
/*   Updated: 2024/05/21 20:47:17 by rileone          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "../../includes/lexer.h"


/**se incontro una redirection controllo che il token successivo sia necessariamente una parola*/


t_token *look_tokens_ahead(t_token *current)
{
	if (current->next == NULL)
		return (NULL);
	if (current->next->type != WORD_TOKEN && current->next->type != WHITESPACE_TOKEN)
		return (NULL);
	if (current->next->type == WORD_TOKEN)
		return current->next;
	if(current->next->type == WHITESPACE_TOKEN && (current->next->next && current->next->next->type == WORD_TOKEN))
		return current->next->next;
	
	return NULL;
	
}

int check_if_is_a_redirection(t_token *node)
{
	/**bisogna aggiungerci la gestione dell heredoc*/
	if(node->type == GREATER_TOKEN || node->type == REDIR_OUT_TOKEN || node->type == LESSER_TOKEN)
		return (SUCCESS);
	return (0);
}

/**Self explanatory*/

int count_pipes(t_token *head)
{
	t_token *ptr;
	int counter;

	counter = 0;
	ptr = head;
	while(ptr)
	{
		if(ptr->type == PIPE_TOKEN)
			counter++;
		ptr = ptr->next;		
	}
	return counter;
}

/**Copio le informazioni alll interno del nuovo token */

void copy_token_info(t_token **new, t_token *old)
{
	t_token *tmp;

	tmp = *new;

	tmp->value = ft_strdup(old->value);
	tmp->type = old->type;
}

/**La lista di token viene splittata in base alle pipeline per un
 * piu facile parsing delle redirection
*/

t_token *split_command_based_on_pipes(t_token **ptr)
{
	t_token *newlist;
	t_token *newnode;
	
	newlist = NULL;
	while(*ptr && (*ptr)->type != PIPE_TOKEN)
	{
		newnode = token_new(NULL);
		copy_token_info(&newnode, *ptr);
		if(!newnode)
		{
			free_tokens(newlist); 
			return NULL;
		}				
		token_add_back(&newlist, newnode);
		(*ptr) = (*ptr)->next;
	}
	if ((*ptr) && (*ptr)->type == PIPE_TOKEN)
		(*ptr) = (*ptr)->next;
	return newlist;
}

int handle_redirection_logic(t_token *node, t_shell *shell)
{

	t_token *node_ahead;

	if(check_if_is_a_redirection(node))
	{
		node_ahead = look_tokens_ahead(node);
		if (node_ahead == NULL)
			return (ERROR);
		if (node_ahead->type == WORD_TOKEN)
		{
			

			
			printf("redirec to/from  == %s\n", node_ahead->value);
		}
	}
}

int parse_redirections(t_token *head, t_shell *shell)
{
	t_token *tmp_list;
	t_token *node;
	t_token *ptr;
	int n_pipes;
	int i;
	(void)shell;
	
	ptr = head;
	n_pipes = count_pipes(head);
	/***
	 * 
	 * 
	 * -------------------------------------------------------------------
	 * sto facendo una lista non un array tonto, domani guarda questa cosa
	 * -------------------------------------------------------------------
	 * 									|
	 * 									|
	 * 									V
	*/
	shell->cmd_info = ft_calloc(n_pipes + 1, sizeof(t_command));
	i = -1;
	while(ptr && i < n_pipes)
	{
		tmp_list = split_command_based_on_pipes(&ptr);
		node = tmp_list;
		while (node != NULL && node->type != PIPE_TOKEN)
		{
			if (handle_redirection_logic(node, shell) == SUCCESS)
			{
				/**qui vorrei rimuovere i la redirection e l argomento della redirection per poi splittare 
				 * il blocco e ottenere solamente comandi e argomenti.
				*/
			}
			node = node->next;
		}
		free_tokens(tmp_list);
		i++;
	}
	return (SUCCESS);
}


/**Loop principale dove ricevo la stringa e faccio il parsing*/

void read_from_stdin(t_shell *shell)
{
	t_token     *head;
	char		*input;
 	(void)shell;
	while (true)
	{
		input = readline("(MINISHELL)$");
		head = tokenize_input(input, shell);
  		if (head == NULL)
			continue; 
	 	if (syntax_error_handler(head) == ERROR)
		{
			free_tokens(head);
			continue;
		} 
     	if(parse_redirections(head, shell) == ERROR)
			printf("Redirection error\n");
		free(input);
		free_tokens(head);
	}
}

