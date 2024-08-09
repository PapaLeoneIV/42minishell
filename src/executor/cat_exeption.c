/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cat_exeption.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rileone <rileone@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 23:02:54 by codespace         #+#    #+#             */
/*   Updated: 2024/07/18 12:28:47 by rileone          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	put_status(t_shell *shell, int status)
{
	if (g_status_code == 130)
		shell->status = 130;
	else if (status == 131)
	{
		shell->status = 131;
		write(1, "(Quit)Core Dumped\n", 19);
	}
}

int	take_last_pid(t_shell *shell)
{
	int	pid;
	int	tmp;
	int	status;

	pid = 10;
	tmp = 0;
	status = 0;
	while (pid > 0)
	{
		pid = waitpid(-1, &status, 0);
		if (pid > tmp)
		{
			if (WIFEXITED(status))
				shell->status = WEXITSTATUS(status);
			else if (WIFSIGNALED(status))
			{
				put_status(shell, status);
			}
			tmp = pid;
		}
	}
	return (1);
}

void	write_clean(char *cmd, t_shell *shell)
{
	write_exit("bash: ", cmd, ": No such file or directory\n");
	tm_close(shell->s_pip[0], shell->s_pip[1], 0);
	clean_all(shell, 1);
}
