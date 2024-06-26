/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_build.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rileone <rileone@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/07 11:25:20 by fgori             #+#    #+#             */
/*   Updated: 2024/06/26 17:48:33 by rileone          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	exit_path(t_command *cmd, t_shell* shell)
{
	int	argsc;
	int	counter;

	argsc = mtx_count_rows(cmd->cmd);
	counter = 0;
	if (cmd && !cmd->prev && !cmd->next)
		write(1, "exit\n", 5);
	if (argsc == 1)
		g_status_code = 0;
	else if (argsc == 2)
	{
		if (cmd->cmd[1][0] == '+' || cmd->cmd[1][0] == '-')
			counter++;
		while (cmd->cmd[1][counter])
		{
			if (!ft_isdigit(cmd->cmd[1][counter]))
			{
				g_status_code = 2;
				clean_all(shell, 1);
				write(2, "bash: exit: ", 13);
				write(2, cmd->cmd[1], ft_strlen(cmd->cmd[1]));
				write(2, "numeric argument required\n", 27);
				exit(g_status_code);
			}
			counter++;
		}
		g_status_code = (unsigned char)ft_atoi(cmd->cmd[1]);
	}
	else
	{
		write(2, "bash: exit: too many arguments\n", 32);
		g_status_code = 1;
		return (1);
	}
	clean_all(shell, 1);
	exit(g_status_code);
}

