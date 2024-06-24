/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_build.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgori <fgori@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/07 11:25:20 by fgori             #+#    #+#             */
/*   Updated: 2024/06/24 17:28:20 by fgori            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	exit_path(t_command *cmd, t_shell *shell)
{
	unsigned int	exit_status;
	int				i;

	i = 0;
	exit_status = 0;
	open_redir(cmd, shell);
	(void)(close(cmd->in) + close(cmd->out));
	if (mtx_count_rows(cmd->cmd) > 2)
		return (perror("exit\nexit: too many argument"), 300);
	while (cmd->cmd[1] && cmd->cmd[1][i]) // qui ho spostato la prima condizione del while da un if esterno a dentro al while
	{
		if (!ft_isnumber(cmd->cmd[1]) 
			|| cmd->cmd[1][i] == '+' || cmd->cmd[1][i] == '-')
			g_status_code = 2;
		i++;
	}
	if (g_status_code == 2)
		g_status_code = (unsigned int)ft_atoi(cmd->cmd[1]);
	if (g_status_code > 255)
		g_status_code %= 256;
	clean_all(shell, 1);
	exit(g_status_code);
}
