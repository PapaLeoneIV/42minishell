/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_build.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgori <fgori@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/07 11:25:20 by fgori             #+#    #+#             */
/*   Updated: 2024/06/11 15:01:25 by fgori            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


int	exit_path(t_command *cmd, t_shell *shell)
{
	unsigned int	exit_status;
	int 			i;

	i = 0;
	exit_status = 0;
	open_redir(cmd, shell);
	(void)(close(cmd->in) + close(cmd->out));
	if (mtx_count_rows(cmd->cmd) > 2)
		return(perror("exit\nexit: too many argument"), 300);
	if (cmd->cmd[1])
	{
		while (cmd->cmd[1][i++])
		{
			if (!ft_isdigit(cmd->cmd[1][i]))
				exit_status = 2;
			if (!ft_isdigit(cmd->cmd[1][i]))
				perror("Alpha in exit status");
		}
		if (exit_status != 2)
			exit_status = (unsigned int)ft_atoi(cmd->cmd[1]);
		if (exit_status > 255)
			exit_status %= 256;
	}
	clean_all(shell, 1);
	exit(exit_status);
}
