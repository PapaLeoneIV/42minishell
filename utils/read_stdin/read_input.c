/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_input.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rileone <rileone@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/21 17:12:07 by rileone           #+#    #+#             */
/*   Updated: 2024/05/24 20:05:14 by rileone          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "../../includes/lexer.h"
#include "../../includes/executor.h"

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
		input = readline(prompt_path);
		head = tokenize_input(input, shell);
		add_history(input);
  		if (head == NULL)
			continue; 
	 	if (syntax_error_handler(head) == ERROR)
		{
			free_tokens(head);
			continue;
		} 
     	if(parse_redirections(head, shell) == ERROR)
			printf("Redirection error\n");
		/**ho sistemato un po di cose:
		 * - i ritorni delle funzioni.
		 * - alcune assegnazioni.
		 * - ho lassciato qualche commento e un NOTA BENE per l heredoc
		 * - ho creato il .h per le funzione dell executioner
		*/
		if (execute_cmd(&shell) == ERROR)
		{
			/**da vedere come gestire l errore*/
		}
		free(input);
		free_tokens(head);
		free(prompt_path);
	}
}

