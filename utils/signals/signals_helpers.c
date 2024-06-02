/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals_helpers.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/01 11:41:05 by rileone           #+#    #+#             */
/*   Updated: 2024/06/02 09:00:23 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"


void handle_signal(int signum)
{
	if (signum == SIGINT)
	{
		write(1, "\n", 1);
		rl_on_new_line();	
		rl_replace_line("", 0);
		rl_redisplay();
	}	
}

void handle_ctrl_d(t_shell *shell, char *input)
{
	clean_all(shell);
	free(input);
	write(1, "\nexit", 5);	//questo ci va? o lo hai usato come controllo?
	exit(1);
}

void set_signal_handler(struct sigaction *signal_g)
{
	signal_g->sa_handler = handle_signal;
	sigaction(SIGINT, signal_g, NULL);
	signal(SIGQUIT, SIG_IGN);
}