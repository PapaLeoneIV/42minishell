/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_input.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgori <fgori@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/21 17:12:07 by rileone           #+#    #+#             */
/*   Updated: 2024/07/05 15:06:19 by fgori            ###   ########.fr       */
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

void	close_all_fd(int flag)
{
	int			i;
	struct stat	statbuf;

	i = 0;
	if (flag == 2)
		i = 3;
	if (flag)
	{
		while (i <= 1026)
		{
			if (fstat(i, &statbuf) != -1)
				close(i);
			i++;
		}
	}
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
		execute_cmd(shell);
		close_all_fd(2);
		clean_all(shell, 0);
	}
	close_all_fd(1);
}
