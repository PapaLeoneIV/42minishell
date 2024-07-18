/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgori <fgori@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 13:27:42 by fgori             #+#    #+#             */
/*   Updated: 2024/07/18 13:38:29 by fgori            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	gnl2(char **line)
{
	char	*buf;
	int		i;
	int		n;
	char	ch;

	buf = (char *)ft_calloc(10000, 1);
	i = 1;
	n = 0;
	ch = '\0';
	while (i > 0 && ch != '\n')
	{
		i = read(0, &ch, 1);
		if (i < 0)
			return (free(buf), 0);
		buf[n] = ch;
		n++;
	}
	*line = ft_strdup(buf);
	if (!line)
		return (free(buf), 0);
	free(buf);
	return (n);
}

char	**mtx_dup(char **mtx, int len)
{
	char	**out;
	int		i;

	i = 0;
	out = ft_calloc(len + 1, sizeof(char *));
	while (i < len)
	{
		out[i] = ft_strdup(mtx[i]);
		i++;
	}
	return (out);
}

char	*here_rename(char *filename)
{
	int	i;

	while (access(filename, F_OK) == 0)
	{
		i = ft_strlen(filename) - 1;
		if ((filename[i] >= 'a' && filename[i] < 'z')
			|| (filename[i] >= 'A' && filename[i] <= 'Z'))
			filename[i]++;
		else if (filename[i] == 'z')
			filename[i] = 65;
	}
	return(filename);
}

int	tm_close(int tm_in, int tm_out, int flag)
{
	struct stat	st;
	if (flag)
	{
		dup2(tm_in, 0);
		dup2(tm_out, 1);
	}
	if (fstat(tm_in, &st) == 0)
		close(tm_in);
	if (fstat(tm_out, &st) == 0)
		close(tm_out);
	return (1);
}

int	set_pip(t_command *cmd, int *pip)
{
	if ((cmd->cmd_id == 0 && cmd->next != NULL)
		|| (cmd->cmd_id != 0))
		if (pipe(pip) < 0)
			return (perror("ERROR while opening the pipe\n"), ERROR);
	if (cmd->next)
	{
		close(cmd->out);
		cmd->out = pip[1];
		close(cmd->next->in);
		cmd->next->in = pip[0];
		cmd->next->fd_change++;
	}
	return (1);
}
