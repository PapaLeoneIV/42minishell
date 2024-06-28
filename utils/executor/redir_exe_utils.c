/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_exe_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rileone <rileone@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 13:26:16 by fgori             #+#    #+#             */
/*   Updated: 2024/06/28 13:13:56 by rileone          ###   ########.fr       */
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
			write(2, " Permission denied\n", 18);
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

int	check_valid_line(char *line)
{
	if (line && *line == '\0')
		return (ERROR);
	return (SUCCESS);
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
		if (cmd->out == -1 || cmd->in == -1) //
			return (ERROR);                  //qui poi fd->change diventa (-1)
		else if (cmd->in == -2)
			return (-2);
	}
	return (1);
}
