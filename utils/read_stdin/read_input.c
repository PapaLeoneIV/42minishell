/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_input.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rileone <rileone@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/21 17:12:07 by rileone           #+#    #+#             */
/*   Updated: 2024/05/22 22:35:40 by rileone          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "../../includes/lexer.h"

/**Loop principale dove ricevo la stringa e faccio il parsing*/

void read_from_stdin(t_shell *shell)
{
	t_token     *head;
	char		*input;
	char	*prompt_path;
 	(void)shell;
	while (true)
	{
		prompt_path = get_directory_path();
		input = readline("(MINISHELL)$");
		head = tokenize_input(input, shell);
		add_history(input);
  		if (head == NULL)
			continue; 
	 	if (syntax_error_handler(head) == ERROR)
		{
			free_tokens(head);
			continue;
		} 
		//forse in futuro sara' necessario farsi una copia della lst di token
     	if(parse_redirections(head, shell) == ERROR)
			printf("Redirection error\n");
		free(input);
		free_tokens(head);
		free(prompt_path); 
	}
}

