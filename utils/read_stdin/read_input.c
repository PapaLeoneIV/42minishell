/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_input.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgori <fgori@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/21 17:12:07 by rileone           #+#    #+#             */
/*   Updated: 2024/05/28 11:15:59 by fgori            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "../../includes/lexer.h"
#include "../../includes/executor.h"

/**Loop principale dove ricevo la stringa e faccio il parsing*/

#include <stdio.h>

// Function to print the contents of the t_command and t_redir structures
void print_shell_info(t_shell *shell)
{
    if (shell == NULL || shell->cmd_info == NULL) {
        printf("No command information available.\n");
        return;
    }

    t_command *cmd_info = *shell->cmd_info;
    while (cmd_info != NULL) {
        printf("Command ID: %d\n", cmd_info->cmd_id);
        
        printf("Command: ");
        if (cmd_info->cmd != NULL) {
            for (int j = 0; cmd_info->cmd[j] != NULL; j++) {
                printf("%s ", cmd_info->cmd[j]);
            }
            printf("\n");
        } else {
            printf("No command.\n");
        }


        if (cmd_info->redirection_info != NULL) {
            t_redir *redir_info = *cmd_info->redirection_info;
            while (redir_info != NULL) {
                printf("Redirection - In: %d, Out: %d, Type: %d, Filename: %s\n", redir_info->in, redir_info->out, redir_info->type_of_redirection, redir_info->filename);
                redir_info = redir_info->next;
            }
        } else {
            printf("No redirection information.\n");
        }
        printf("\n");

        cmd_info = cmd_info->next;
    }
}


void read_from_stdin(t_shell *shell)
{
	t_token     *head;
	char		*input;
	char	*prompt_path;
	
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
     	if(parse_redirections(head, shell) == ERROR)
			printf("Redirection error\n");
		/**ho sistemato un po di cose:
		 * - i ritorni delle funzioni.
		 * - alcune assegnazioni.
		 * - ho lassciato qualche commento e un NOTA BENE per l heredoc
		 * - ho creato il .h per le funzione dell executioner
		*/
		if (execute_cmd(shell) == ERROR)
		{
			/**da vedere come gestire l errore*/
		}
		free(input);
		free_tokens(head);
		free(prompt_path); 
	}
}

