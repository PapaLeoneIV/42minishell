/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_maker.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 10:52:33 by fgori             #+#    #+#             */
/*   Updated: 2024/05/25 12:48:01 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	list_of_out(t_redir *dir)
{
	int	fd;

	if (dir->type_of_redirection == GREATER_TOKEN)
	{
		while (dir && dir->type_of_redirection == GREATER_TOKEN)
		{
			fd = open(dir->filename,  O_TRUNC | O_CREAT | O_RDWR, 0777);
			if (fd < 0)
				return (perror("ERROR\nin file opening"), ERROR);
			if (dir->next)
				close(fd);
			dir = dir->next;
		}
	}
	else
	{
		while (dir && dir->type_of_redirection == REDIR_OUT_TOKEN)
		{
			fd = open(dir->filename,  O_APPEND | O_CREAT | O_RDWR, 0777);
			if (fd < 0)
				return (printf("%s: No such file or directory", dir->filename), ERROR);
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
	
	while (dir && dir->type_of_redirection == LESSER_TOKEN)
	{
		fd = open(dir->filename, O_RDONLY, 0777);
		if (fd < 0)
			return(printf("%s: No such file or directory", dir->filename), ERROR);
		if (dir->next)
			close(fd);
		dir = dir->next;   
	}
	return (fd);
}

int	execution(t_command *cmd, t_env **env)
{
	t_redir	*tmp;
	/**Note da osservare credo:
	 * - l heredoc deve essere la prima cosa che va eseguita da quello che ho visto, (va cercato se c e' un 
	 * 			HEREDOC_TOKEN con associato WORD_TOKEN/HEREDOC_TOKEN_WITH_QUOTES) e va startato il prompt 
	 * 			di heredoc prima di ogni altro comando. Il contenuto dell heredoc va poi visto se essere espanso oppure no.
	 * - 
	*/
	//dovrei aver aggiustato la cosa, adesso la memoria viene allocata solo nel caso in cui si trovino delle redirection quindi se non ve ne sono il programma va avanti seguendo l'if
	tmp = (*cmd->redirection_info);
	while (tmp)
	{
		if (tmp->type_of_redirection  == GREATER_TOKEN
			|| tmp->type_of_redirection  == REDIR_OUT_TOKEN)
			cmd->out = list_of_out(tmp);
		else if (tmp->type_of_redirection  == LESSER_TOKEN)
			cmd->in = list_of_in(tmp);
		/* else
			heardoc_path(); */
		
	}
	//dup2(pip[0], cmd->in);
	//dup2(pip[1], cmd->out);
	cmd->fork_id = fork();
	if (cmd->fork_id == 0)
	{
		//close(pip[0]);
/* 		make_things() */
	}
	else
	{
		//close(pip[1]);
		//dup2(pip[0], STDIN_FILENO);
	}
	return SUCCESS;
}

int	execute_cmd(t_shell *shell)
{
	t_command *cmd;

	cmd = (*shell->cmd_info);
	if (pipe(shell->shell_pip) < 0)
		return(perror ("ERROR while opening the pipe\n"), ERROR);
	while(cmd)
	{
		if (execution(cmd, shell->env) == ERROR)
		{
			
			perror("ERROR");
			return (ERROR);
		}
		cmd = cmd->next;
	}
	waitpid(-1, NULL, 0);
	return (SUCCESS);
}
