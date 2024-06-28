/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_build.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rileone <rileone@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/07 11:25:20 by fgori             #+#    #+#             */
/*   Updated: 2024/06/28 11:26:19 by rileone          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void check_args(t_command *cmd)
{
	if (cmd && !cmd->prev && !cmd->next)
		write(1, "exit\n", 5);
}

static void exit_num_error(t_command *cmd, t_shell *shell)
{
	g_status_code = 2;
	write_exit("bash: exit: ", cmd->cmd[1], " :numeric argument required\n");
	clean_all(shell, 1);
	exit(g_status_code);
} 

static void handle_exit_wrong_args(void)
{
	write(2, "bash: exit: too many arguments\n", 32);
	g_status_code = 1;
}
int	exit_path(t_command *cmd, t_shell *shell)
{	
	int	counter;
	int argsc;

	argsc = mtx_count_rows(cmd->cmd);
	counter = 0;
	check_args(cmd);
	if (argsc == 1)
		g_status_code = 0;
	else if (argsc == 2)
	{
		if (cmd->cmd[1][0] == '+' || cmd->cmd[1][0] == '-')
			counter++;
		while (cmd->cmd[1][counter])
		{
			if (!ft_isdigit(cmd->cmd[1][counter++]))
				exit_num_error(cmd, shell);
		}
		g_status_code = (unsigned char)ft_atoi(cmd->cmd[1]);
	}
	else
		return (handle_exit_wrong_args(),1);
	clean_all(shell, 1);
	exit(g_status_code);
}