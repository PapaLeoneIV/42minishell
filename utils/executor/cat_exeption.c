/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cat_exeption.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgori <fgori@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 23:02:54 by codespace         #+#    #+#             */
/*   Updated: 2024/07/15 19:05:57 by fgori            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	write_line(int cat, t_shell *shell)
{
	char	*line;

	signal(SIGINT, handle_signal_cat);
	signal(SIGQUIT, SIG_DFL);
	while (cat > 0)
	{
		gnl2(&line);
		if (*line == 0)
		{
			free(line);
			break ;
		}
		free(line);
		if (g_status_code == 130)
			break ;
		cat--;
	}
	clean_all(shell, 1);
}

int	cat_check(t_command *cmd)
{
	t_command	*tmp;
	int			i;

	tmp = cmd;
	i = 0;
	if (tmp->cmd_id == 0 && ft_strncmp(tmp->cmd[0], "cat", 4) == 0)
	{
		while (tmp && ft_strncmp(tmp->cmd[0], "cat", 4) == 0
			&& !cmd->cmd[1] && !cmd->redirection_info)
		{
			tmp->cat = 1;
			i++;
			tmp = tmp->next;
		}
	}
	if (tmp && ft_strncmp(tmp->cmd[0], "cat", 4) != 0)
		return (i);
	else
		return (0);
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
				if (g_status_code == 130)
					shell->status = 130;
				else
					shell->status = 131;
			}
			tmp = pid;
		}
	}
	return (1);
}

void	write_clean(char *cmd, t_shell *shell)
{
	write_exit("bash: ", cmd, ": No such file or directory\n");
	clean_all(shell, 1);
}
