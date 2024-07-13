/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_input.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/21 17:12:07 by rileone           #+#    #+#             */
/*   Updated: 2024/07/13 11:00:44 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	tokenizer(t_shell *shell, char *input, t_token **head)
{
	*head = tokenize_input(input, shell);
	if (*head == NULL)
	{
		if (g_status_code == 130)
			shell->status = 130;
		return (ERROR);
	}
	return (SUCCESS);
}

static int	lexer(t_token **head, t_shell *shell)
{
	if (syntax_error_handler(head) == ERROR)
	{
		free_tokens(*head);
		shell->status = 2;
		if (g_status_code == 130)
			shell->status = 130;
		return (ERROR);
	}
	if (parse_redirections(*head, shell) == ERROR)
		write(2, "redirection error", 18);
	return (SUCCESS);
}

void	read_from_stdin(t_shell *shell, char **envp)
{
	t_token	*head;
	char	*input;

	head = NULL;
	shell->env = get_env_info(envp);
	while (true)
	{
		signal(SIGINT, handle_signal);
		signal(SIGQUIT, SIG_IGN);
		input = readline("(MINISHELL)$ ");
		if (!input)
			handle_ctrl_d(shell, input);
		add_history(input);
		if (tokenizer(shell, input, &head) == ERROR)
			continue ;
		free(input);
		if (lexer(&head, shell) == ERROR)
			continue ;
		free_tokens(head);
		g_status_code = 0;
		execute_cmd(shell);
		clean_all(shell, 0);
	}
}
