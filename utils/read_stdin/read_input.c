/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_input.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rileone <rileone@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/21 17:12:07 by rileone           #+#    #+#             */
/*   Updated: 2024/06/27 16:55:33 by rileone          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	tokenizer(t_shell *shell, char *input, t_token **head)
{
	*head = tokenize_input(input, shell);
	if (*head == NULL)
		return (ERROR);
	return (SUCCESS);
}

static int	lexer(t_token **head, t_shell *shell)
{
	if (syntax_error_handler(head) == ERROR)
	{
		free_tokens(*head);
		g_status_code = 2;
		return (ERROR);
	}
	if (parse_redirections(*head, shell) == ERROR)
		;
	return (SUCCESS);
}

void	read_from_stdin(t_shell *shell, char **envp)
{
	t_token	*head;
	char	*input;

	head = NULL;
	signal(SIGINT, handle_signal);
	signal(SIGQUIT, SIG_IGN);
	shell->env = get_env_info(envp);
	while (true)
	{
		input = readline("(MINISHELL)$ ");
		if (!input)
			handle_ctrl_d(shell, input);
		if (tokenizer(shell, input, &head) == ERROR)
			continue ;
		add_history(input);
		free(input);
		if (lexer(&head, shell) == ERROR)
			continue ;
		free_tokens(head);
		execute_cmd(shell);
		clean_all(shell, 0);
	}
}
