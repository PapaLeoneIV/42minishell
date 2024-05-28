/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_maker.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgori <fgori@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 10:52:33 by fgori             #+#    #+#             */
/*   Updated: 2024/05/28 13:41:27 by fgori            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	list_of_out(t_redir **dir)
{
	int	fd;

	if ((*dir)->type_of_redirection == GREATER_TOKEN)
	{
		while ((*dir) && (*dir)->type_of_redirection == GREATER_TOKEN)
		{
			fd = open((*dir)->filename,  O_TRUNC | O_CREAT | O_RDWR, 0777);
			if (fd < 0)
				break ;
			if ((*dir)->next)
				close(fd);
			(*dir) = (*dir)->next;
		}
	}
	else
	{
		while ((*dir) && (*dir)->type_of_redirection == REDIR_OUT_TOKEN)
		{
			fd = open((*dir)->filename,  O_APPEND | O_CREAT | O_RDWR, 0777);
			if (fd < 0)
				break ;
			if ((*dir)->next)
				close(fd);
			(*dir) = (*dir)->next;
		}
	}
	if (fd < 0)
		{
			printf("impossible to open: %s\n", (*dir)->filename);
			return (-1);
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
			printf("%s: No such file or directory\n", (*dir)->filename);
			(*dir) = (*dir)->next;
			return(-1);
		}
		if ((*dir)->next)
			close(fd);
		(*dir) = (*dir)->next;   
	}
	return (fd);
}

void	freeall(char **mat)
{
	int	n;

	n = 0;
	while (mat[n])
	{
		free(mat[n]);
		mat[n] = NULL;
		n++;
	}
	free(mat);
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
	freeall(open_path);
	if (!supp)
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
		if (!(*tmp))
			break ;
		if ((*tmp)->type_of_redirection  == GREATER_TOKEN
			|| (*tmp)->type_of_redirection  == REDIR_OUT_TOKEN)
			cmd->out = list_of_out(&(*tmp));
		else if ((*tmp)->type_of_redirection  == LESSER_TOKEN)
			cmd->in = list_of_in(&(*tmp));
		/* else
			heardoc_path(); */
		if (cmd->in == -1 || cmd->out == -1)
			return (ERROR);	
	}
	printf ("in e : %d, mentr out: %d", cmd->in,cmd->out);
	dup2(cmd->in, 0);
	dup2(cmd->out, 1);
	cmd->fork_id = fork();
	if (cmd->fork_id == 0)
	{
		//if (cmd->next)
		//	close(shell->shell_pip[0]);
 		make_things(cmd->cmd, find_node(env, "PATH")); 
	}
	else
	{
		//close(shell->shell_pip[1]);
		//dup2(shell->shell_pip[0], STDIN_FILENO);
	}
	return SUCCESS;
}

int	execute_cmd(t_shell *shell)
{
	t_command	*cmd;
	int			tm_in;
	int			tm_out;

	cmd = (*shell->cmd_info);
	tm_in = dup(0);
	tm_out = dup(1);
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
	dup2(tm_in, 0);
	dup2(tm_out, 1);
	return (SUCCESS);
}
