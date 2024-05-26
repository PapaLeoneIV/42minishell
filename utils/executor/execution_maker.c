/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_maker.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 10:52:33 by fgori             #+#    #+#             */
/*   Updated: 2024/05/26 12:16:01 by codespace        ###   ########.fr       */
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

int	make_things(char **cmd, t_env *path)
{
	char	**open_path;
	char	*tmp;
	char	*supp;
	int		i;

	i = 0;
	open_path = ft_split(path->body, ':');
	while (open_path[i])
	{
		tmp = ft_strjoin(open_path[i], "/");
		supp = ft_strjoin(tmp, cmd[0]);
		free(tmp);
		if (access(supp, F_OK | X_OK) == 0)
			break ;
		free (supp);
		i++;
	}
	ft_clear_mtx(&open_path, mtx_count_rows(path->env_mtx));
	if (i == mtx_count_rows(path->env_mtx))
		return (perror("access don't replies"), -1);
	if (execve(supp, cmd, path->env_mtx) < 0)
		perror("ERROR\n execve don't replies");
	free(supp);
	return (1);
}

// da lavorare non completa!!!!!
int	execution(t_command *cmd, t_env **env, t_shell *shell)
{
	t_redir	**tmp;
	/**Note da osservare credo:
	 * - l heredoc deve essere la prima cosa che va eseguita da quello che ho visto, (va cercato se c e' un 
	 * 			HEREDOC_TOKEN con associato WORD_TOKEN/HEREDOC_TOKEN_WITH_QUOTES) e va startato il prompt 
	 * 			di heredoc prima di ogni altro comando. Il contenuto dell heredoc va poi visto se essere espanso oppure no.
	 * - 
	*/
	if (cmd->next)
		dup2(cmd->in, shell->shell_pip[0]);
	if (cmd->prev)	
		dup2(cmd->out, shell->shell_pip[1]);
	//dovrei aver aggiustato la cosa, adesso la memoria viene allocata solo nel caso in cui si trovino delle redirection quindi se non ve ne sono il programma va avanti seguendo l'if
	tmp = cmd->redirection_info;
	while (tmp)
	{
		if ((*tmp)->type_of_redirection  == GREATER_TOKEN
			|| (*tmp)->type_of_redirection  == REDIR_OUT_TOKEN)
			cmd->out = list_of_out((*tmp));
		else if ((*tmp)->type_of_redirection  == LESSER_TOKEN)
			cmd->in = list_of_in((*tmp));
		/* else
			heardoc_path(); */
		
	}
	dup2(cmd->in, 0);
	dup2(cmd->out, 1);
	cmd->fork_id = fork();
	if (cmd->fork_id == 0)
	{
		if (cmd->next)
		close(shell->shell_pip[0]);
 		make_things(cmd->cmd, find_node(env, "PATH")); 
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
	if (cmd->next != NULL)
		if (pipe(shell->shell_pip) < 0)
			return(perror ("ERROR while opening the pipe\n"), ERROR);
	while(cmd)
	{
		if (execution(cmd, shell->env, shell) == ERROR)
		{
			
			perror("ERROR");
			return (ERROR);
		}
		cmd = cmd->next;
	}
	waitpid(-1, NULL, 0);
	return (SUCCESS);
}
