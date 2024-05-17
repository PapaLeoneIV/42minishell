/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_input.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rileone <rileone@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/21 17:12:07 by rileone           #+#    #+#             */
/*   Updated: 2024/05/17 17:06:05 by rileone          ###   ########.fr       */
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

int parse_redirections(t_token *head, t_shell *shell)
{
	t_token *current;
	t_token *tmp;
/* 	int i;

	i = 0; */
	current = head;
	
	while (current != NULL)
	{
		/**reset everything before next loop*/
			if (current->type == GREATER_TOKEN)
			{
				tmp = look_tokens_ahead(current);
				if (tmp == NULL)
					return (0);
				if (tmp->type == WORD_TOKEN)
				{
					
				}
			}
		/**need to develop rules even for LESSER >> and maybe heredoc*/
		current = current->next;
	}
	(void)shell;
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
 		/* if (head == NULL)
			continue; 
	 	if (syntax_error_handler(head) == 0)
			printf("SYNTAX ERROR NEAR UNEXPECTED TOKEN\n");
	   	if( parse_redirections(head, shell) == 0)
			printf("Redirection error\n");
		free(input);
		input = NULL;  
		free_tokens(head); */
/* 		exit(1); */
	}
}

