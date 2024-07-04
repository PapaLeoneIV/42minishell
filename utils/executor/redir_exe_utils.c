/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_exe_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rileone <rileone@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 13:26:16 by fgori             #+#    #+#             */
/*   Updated: 2024/07/04 13:52:10 by rileone          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	list_of_out(t_redir **dir)
{
	int	fd;
	int	redir;

	redir = (*dir)->type_of_redirection;
	while ((*dir) && ((*dir)->type_of_redirection == GREATER_TOKEN
			|| (*dir)->type_of_redirection == REDIR_OUT_TOKEN))
	{
		if ((*dir)->type_of_redirection == GREATER_TOKEN)
			fd = open((*dir)->filename, O_TRUNC | O_CREAT | O_RDWR, 0777);
		else
			fd = open((*dir)->filename, O_APPEND | O_CREAT | O_RDWR, 0777);
		if (fd < 0)
		{
			write(2, " Permission denied\n", 20);
			return (-1);
		}
		if ((*dir)->next && (*dir)->next->type_of_redirection == redir)
			close(fd);
		(*dir) = (*dir)->next;
	}
	return (fd);
}

int	list_of_in(t_redir **dir)
{
	int	fd;

	while ((*dir) && (*dir)->type_of_redirection == LESSER_TOKEN)
	{
		fd = open((*dir)->filename, O_RDONLY, 0777);
		if (fd < 0)
		{
			write(2, (*dir)->filename, ft_strlen((*dir)->filename));
			write(2, " : No such file or directory\n", 30);
			(*dir) = (*dir)->next;
			return (-1);
		}
		if ((*dir)->next && (*dir)->next->type_of_redirection == LESSER_TOKEN)
			close(fd);
		(*dir) = (*dir)->next;
	}
	return (fd);
}

int	open_redir(t_command *cmd, t_shell *shell)
{
	t_redir	*tmp;

	if (!cmd->redirection_info)
		return (1);
	tmp = (*cmd->redirection_info);
	while (tmp)
	{
		if (tmp->type_of_redirection == GREATER_TOKEN
			|| tmp->type_of_redirection == REDIR_OUT_TOKEN)
			cmd->out = list_of_out(&tmp);
		else if (tmp->type_of_redirection == LESSER_TOKEN)
			cmd->in = list_of_in(&tmp);
		else if (tmp->type_of_redirection == HEREDOC_TOKEN)
		{
			if (cmd->here)
				unlink(cmd->here);
			cmd->here = tmp->filename;
			cmd->in = heardoc_path(&tmp, shell);
		}
		if (cmd->out == -1 || cmd->in == -1)
			return (ERROR);
		else if (cmd->in == -2)
			return (-2);
	}
	return (1);
}

static int	set_change(t_command *tmp, int red_st, int *arr, t_shell *shell)
{
	if (red_st == ERROR || red_st == -2)
	{
		shell->status = 1;
		tmp->fd_change = -1;
		if (red_st == -2)
			return (ERROR);
	}
	else
	{
		if (tmp->in != arr[1] && tmp->fd_change == 0)
			tmp->fd_change++;
		if (arr[0] != tmp->out)
			tmp->fd_change += 2;
		return (SUCCESS);
	}
	return (ERROR);
}

int	make_redir(t_shell *shell, t_command *cmd)
{
	int			tm_i;
	int			tm_ou;
	int			red_st;
	t_command	*tmp;

	tmp = cmd;
	while (tmp)
	{
		tm_i = tmp->in;
		tm_ou = tmp->out;
		if (set_pip(tmp, tmp->pip) == ERROR)
			return (ERROR);
		red_st = open_redir(tmp, shell);
		if (set_change(tmp, red_st, (int[2]){tm_ou, tm_i}, shell) == ERROR)
			return (ERROR);
		tmp = tmp->next;
	}
	return (SUCCESS);
}
