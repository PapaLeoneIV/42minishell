/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_input.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rileone <rileone@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/21 17:12:07 by rileone           #+#    #+#             */
/*   Updated: 2024/05/19 19:07:40 by rileone          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "../../includes/lexer.h"


char *join_token_values(t_token *head)
{
	char *joined_values;
	t_token *current;

	current = head;
	joined_values = NULL;
	while (current != NULL)
	{
		joined_values = ft_strjoin(joined_values, current->value);
		current = current->next;
	}
	return joined_values;
}




t_token *look_tokens_ahead(t_token *current)
{
	if (current->next == NULL)
		return (NULL);
	if (current->next->type != WORD_TOKEN && current->next->type != WHITESPACE_TOKEN)
		return (NULL);
	if(current->next->type == WHITESPACE_TOKEN && (current->next->next && current->next->next->type == WORD_TOKEN))
		return current->next->next;
	
	return NULL;
	
}

int check_if_is_a_redirection(t_token *node)
{
	/**bisogna aggiungerci la gestione dell heredoc*/
	if(node->type == GREATER_TOKEN || node->type == REDIR_OUT_TOKEN || node->type == LESSER_TOKEN)
		return (1);
	return (0);
}

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


void copy_token_info(t_token **new, t_token *old)
{
	t_token *tmp;

	tmp = *new;

	tmp->value = old->value; 
	tmp->type = old->type;
	tmp->next = old->next;
	tmp->prev = old->prev;	
}

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

int parse_redirections(t_token *head, t_shell *shell)
{
/* 	t_token *current;
 */	t_token *token_ahead;
	t_token *tmp_list;
	t_token *ptr;
	int n_pipes;
	int i;
	(void)shell;

	/**devo spezzare la lista in base alle pipe.
	 * e analizzare le redirection piu facilmente 
	 * 
	*/
	ptr = head;
	n_pipes = count_pipes(head); /***devo stare attemto se il numero di pipes e' zero */
	i = 0;
	while(ptr && i < n_pipes)
	{
		tmp_list = split_command_based_on_pipes(&ptr);
		while (tmp_list != NULL && tmp_list->type != PIPE_TOKEN)
		{
			if(check_if_is_a_redirection(tmp_list))
			{
				token_ahead = look_tokens_ahead(tmp_list);
				if (token_ahead == NULL)
					return (0);
				if (token_ahead->type == WORD_TOKEN)
				{
					printf("token dopo la redirection == %s\n", token_ahead->value);
					/**inserisci informazioni nella struttura*/
				}
			}
			tmp_list = tmp_list->next;
		}
		free_tokens(tmp_list);
		i++;
	}
	return 1;
}


void read_from_stdin(t_shell *shell)
{
	t_token     *head;
	char		*input;
 	(void)shell;
	while (1)
	{
		input = readline("(MINISHELL)$");
		head = tokenize_input(input, shell);
 		if (head == NULL)
			continue; 
	 	if (syntax_error_handler(head) == 0)
		{
			free_tokens(head);
			continue;
		}
/* 		char *tmp = join_token_values(head); */
	   	if(parse_redirections(head, shell) == 0)
			printf("Redirection error\n");
		free(input);
		input = NULL;  
		free_tokens(head); 
/* 		exit(1); */
	}
}

