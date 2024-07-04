/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals_helpers.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rileone <rileone@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/01 11:41:05 by rileone           #+#    #+#             */
/*   Updated: 2024/07/04 13:55:12 by rileone          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	handle_signal(int signum)
{
	if (signum == SIGINT)
	{
		g_status_code = 130;
		ioctl(0, TIOCSTI, "\n");
		rl_on_new_line();
		rl_replace_line("", 0);
	}
}

void	handle_ctrl_d(t_shell *shell, char *input)
{
	clean_env_lst(shell->env);
	if (shell->line)
		free(shell->line);
	free(input);
	close_all_fd(1);
	rl_clear_history();
	write(1, "exit\n", 5);
	exit(shell->status);
}
