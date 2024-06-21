/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_input.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rileone <rileone@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/21 17:12:07 by rileone           #+#    #+#             */
/*   Updated: 2024/06/21 12:41:23 by rileone          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

 struct sigaction signal_g;

void read_from_stdin(t_shell *shell, char **envp)
{
	t_token     *head;
	char		*input;
	char		*prompt_path;

	memset(&signal_g, 0, sizeof(signal_g));
	set_signal_handler(&signal_g, 1);
	shell->env = get_env_info(envp);
	while (true)
	{
		prompt_path = get_directory_path();
		input = readline("(MINISHELL)$ ");
		if (!input)
			handle_ctrl_d(shell, input, prompt_path);
		free(prompt_path); 
		head = tokenize_input(input, shell);
		add_history(input);
		free(input);
  		if (head == NULL)
			continue; 
	 	if (syntax_error_handler(head) == ERROR)
		{
			free_tokens(head);
			continue;
		}
     	if(parse_redirections(head, shell) == ERROR)
			printf("Redirection error\n");
		free_tokens(head);
 		if (execute_cmd(shell) == ERROR)
		{
		}
		clean_all(shell, 0);
	}
}

