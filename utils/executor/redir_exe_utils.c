/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_exe_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 13:26:16 by fgori             #+#    #+#             */
/*   Updated: 2024/07/13 12:08:03 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	list_of_out(t_redir **dir)
{
	int	fd;

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
		if ((*dir)->next && ((*dir)->next->type_of_redirection == GREATER_TOKEN
				|| (*dir)->next->type_of_redirection == REDIR_OUT_TOKEN))
			close(fd);
		(*dir) = (*dir)->next;
	}
	return (fd);
}

static int	list_of_in(t_redir **dir, t_command *cmd)
{
	int	fd;

	close (cmd->in);
	while ((*dir) && (*dir)->type_of_redirection == LESSER_TOKEN)
	{
		fd = open((*dir)->filename, O_RDONLY, 0777);
		if (fd < 0)
		{
			return (-1);
		}
		if ((*dir)->next && (*dir)->next->type_of_redirection == LESSER_TOKEN)
			close(fd);
		(*dir) = (*dir)->next;
	}
	return (fd);
}

int	open_redir(t_command *cmd, t_shell *shell, t_redir **redir, int flag)
{
	t_redir	*tmp;

	if (!cmd->redirection_info)
		return (1);
	tmp = (*redir);
	while (tmp)
	{
		if ((tmp->type_of_redirection == GREATER_TOKEN
			|| tmp->type_of_redirection == REDIR_OUT_TOKEN) && flag)
			cmd->out = list_of_out(&tmp);
		else if (tmp->type_of_redirection == LESSER_TOKEN && flag)
			cmd->in = list_of_in(&tmp, cmd);
		else if (tmp->type_of_redirection == HEREDOC_TOKEN)
		{
			if (cmd->here)
				unlink(cmd->here);
			cmd->here = tmp->filename;
			cmd->in = heardoc_path(&tmp, shell);
		}
		else if (!flag)
			tmp = tmp->next;
		if (cmd->out == -1 || cmd->in == -1 || cmd->in == -2)
			return (error_fd_managemnt(cmd, shell, tmp));
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
		red_st = open_redir(tmp, shell, tmp->redirection_info, SUCCESS);
		if (red_st == -2)
		{
			shell->status = 130;
			return (2);
		}
		set_change(tmp, red_st, (int [2]){tm_ou, tm_i}, shell);
		tmp = tmp->next;
	}
	return (SUCCESS);
}
