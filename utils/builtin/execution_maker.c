/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_maker.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgori <fgori@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 10:52:33 by fgori             #+#    #+#             */
/*   Updated: 2024/05/24 13:55:27 by fgori            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	list_of_out(t_redir *dir)
{
	int	fd;

	if (dir->type_of_redirection == GREATER_TOKEN)
	{
		while (dir)
		{
			fd = open(dir->filename,  O_TRUNC | O_CREAT | O_RDWR, 0777);
			if (fd < 0)
				return (perror("ERROR\nin file opening"), -1);
			if (dir->next)
				close(fd);
			dir = dir->next;
		}
	}
	else
	{
		while (dir)
		{
			fd = open(dir->filename,  O_APPEND | O_CREAT | O_RDWR, 0777);
			if (fd < 0)
				return (perror("ERROR\nin file opening"), -1);
			if (dir->next)
				close(fd);
			dir = dir->next;
		}
	}
	return (fd);
}

int	list_of_in(t_redir *dir)
{
	int	fd;
	
	while (dir)
	{
		fd = open(dir->filename, O_RDONLY, 0777);
		if (fd < -1)
			return(perror("ERROR\nin opening input"), -1);
		if (dir->next)
			close(fd);
		dir->next;
	}
	return (fd);
}

int	execution(t_command *cmd, t_env **env)
{
	int	*pip[2];

	if (pipe(pip) < 0)
		return(perror ("ERROR\nanopen pipe"), 0);
	if (cmd->redirection_info)
	{
		if ((*cmd->redirection_info)->type_of_redirection  == GREATER_TOKEN
			|| (*cmd->redirection_info)->type_of_redirection  == REDIR_OUT_TOKEN)
			cmd->out = list_of_out((*cmd->redirection_info));
		else if ((*cmd->redirection_info)->type_of_redirection  == LESSER_TOKEN)
			cmd->in = list_of_in((*cmd->redirection_info));
		else
			heardoc_path();
		
	}
	dup2(pip[0], cmd->in);
	dup2(pip[1], cmd->out);
	cmd->fork_id = fork();
	if (cmd->fork_id == 0)
	{
		close(pip[0]);
		make_things()
	}
	else
	{
		close(pip[1]);
		dup2(pip[0], 0);
	}
}

int	*execute_cmd(t_shell **shell)
{
	t_command *cmd;

	cmd = (*shell)->cmd_info;
	while(cmd)
	{
		if (execution(cmd, (*shell)->env) == 0)
		{
			perror("ERROR");
			return (-1);
		}
		cmd = cmd->next;
	}
	waitpid(-1, NULL, 0);
	return (1);
}
