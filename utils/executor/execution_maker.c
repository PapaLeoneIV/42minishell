/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_maker.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rileone <rileone@student.42.fr>            +#+  +:+       +#+        */
/*                                            	    +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 11:20:59 by fgori             #+#    #+#             */
/*   Updated: 2024/06/28 11:30:09 by rileone          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// Funzione per stampare i file descriptors con colori
// Funzione per stampare i file descriptors con colori
void print_fd(int fd)
{
    printf("\033[1;34m%d\033[0m", fd); // Colore blu per i file descriptors
}

// Funzione per stampare le informazioni di t_redir
void print_redir_info(t_redir *redir)
{
    while (redir != NULL)
    {
        printf("Redirection In: ");
        print_fd(redir->in);
        printf("\nRedirection Out: ");
        print_fd(redir->out);
        printf("\nType of Redirection: %d\n", redir->type_of_redirection);
        printf("Heredoc Expansion: %d\n", redir->heredoc_expansion);
        printf("Filename: %s\n", redir->filename ? redir->filename : "NULL");
        redir = redir->next;
    }
}

// Funzione per stampare le informazioni di t_command
void print_command_info(t_command *cmd)
{
    while (cmd != NULL)
    {
        printf("Command ID: %d\n", cmd->cmd_id);
        printf("Fork ID: %d\n", cmd->fork_id);
        printf("Command: ");
        if (cmd->cmd != NULL)
        {
            for (int i = 0; cmd->cmd[i] != NULL; i++)
            {
                printf("%s ", cmd->cmd[i]);
            }
        }
        else
        {
            printf("NULL");
        }
        printf("\nPipe: ");
        print_fd(cmd->pip[0]);
        printf(" ");
        print_fd(cmd->pip[1]);
        printf("\nInput FD: ");
        print_fd(cmd->in);
        printf("\nOutput FD: ");
        print_fd(cmd->out);
        printf("\nFD Change: %d\n", cmd->fd_change);
        printf("Here: %s\n", cmd->here ? cmd->here : "NULL");

        if (cmd->redirection_info != NULL && *cmd->redirection_info != NULL)
        {
            printf("Redirection Info:\n");
            print_redir_info(*cmd->redirection_info);
        }

        cmd = cmd->next;
    }
}

// Funzione per stampare le informazioni di t_shell
void print_shell_info(t_shell *shell)
{
    printf("Shell Line: %s\n", shell->line);
    printf("Shell Pipe: ");
    print_fd(shell->shell_pip[0]);
    printf(" ");
    print_fd(shell->shell_pip[1]);
    printf("\n");

    if (shell->cmd_info != NULL && *shell->cmd_info != NULL)
    {
        printf("Command Info:\n");
        print_command_info(*shell->cmd_info);
    }

    if (shell->status != NULL)
    {
        printf("Shell Status: %d\n", *(shell->status));
    }
}


void	make_things(t_command *cmd, t_env *path, t_env **env, t_shell *shell)
{
	char	**open_path;
	char	*supp;
	char	**mtx;
	char	**tmp_cmd;
	char	**tmp_env;

	mtx = cmd->cmd;
	if (ft_biltin(cmd, env, shell) == -1)
	{
		tmp_cmd = mtx_dup(mtx, mtx_count_rows(mtx));
		tmp_env = mtx_dup((*env)->env_mtx, mtx_count_rows((*env)->env_mtx));
		if (path)
		{
			open_path = ft_split(path->body, ':');
			supp = ft_access(open_path, tmp_cmd[0]);
			if (!supp)
			{
				g_status_code = 127;
				perror("ERROR\nunfinded path");
				freeall(tmp_cmd);
				return (freeall(open_path), freeall(tmp_env), clean_all(shell,
						1));
			}
			freeall(open_path);
		}
		else
			supp = ft_strdup(cmd->cmd[0]);
		clean_all(shell, 1);
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
		if (execve(supp, tmp_cmd, tmp_env) < 0)
		{
			g_status_code = 126;
			free(supp);
			freeall(tmp_cmd);
			freeall(tmp_env);
			return ;
		}
		free(supp);
	}
	clean_all(shell, 1);
	return ;
}

void	child_process(t_shell *shell, t_command *cmd)
{
	t_env	*tmp;

	if (cmd->fd_change == 1 || cmd->fd_change == 3)
	{
		dup2(cmd->in, 0);
		close(cmd->in);
	}
	if (cmd->fd_change == 2 || cmd->fd_change == 3)
	{
		dup2(cmd->out, 1);
		close(cmd->out);
	}
	tmp = find_node(shell->env, "PATH");
	if (tmp == NULL && access(cmd->cmd[0], F_OK) != 0 && !is_a_biltin(cmd->cmd))
		write_exit("bash: ", "cmd->cmd[0]: ", ": No such file or directory\n");
	else if (cmd->fd_change >= 0)
		// <---qui quando non trovi la redirection input(cmd->in == -1) e
		make_things(cmd, tmp, shell->env, shell);
	//non scriviamo niente dentro la pipe
	else
		clean_all(shell, 1);
	exit(g_status_code);
}

void	fork_and_ecseve(t_shell *shell, t_command *cmd)
{
	if (cmd && cmd->cmd && ft_strncmp(cmd->cmd[0], "exit", 5) == 0)
		waitpid(-1, NULL, 0);
	if (cmd->cmd)
		cmd->fork_id = fork();
	if (cmd->fork_id == 0)
	{
		if (cmd->next)
			close(cmd->pip[0]);
		if (cmd->prev)
			close(cmd->pip[1]);
		child_process(shell, cmd);
	}
	else
	{
		if (cmd->here)
		{
			unlink(cmd->here);
		}
		if (cmd->next)
			close(cmd->pip[1]);
		if (cmd->in != 0 && cmd->in != -1)
			close(cmd->in);
		if (cmd->out != 1 && cmd->out != -1)
			close(cmd->out);
	}
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
		if (red_st == ERROR || red_st == -2) /*<----gestendoli insieme i due ritorni dell errore abbiamo problemi
													quando non abbiamo i permessi per un file perche l exit status
													viene settato ugualmente ad 1 invece che a 0 */
		{
			g_status_code = 1;  
			tmp->fd_change = -1;
								//<-----nel caso di "cat < missing | cat"/"cat < missing | grep hi"
			if (red_st == -2)   //qui lo setti a -1 da dentro linea:126
				return (ERROR);
		}
		else
		{
			if (tmp->in != tm_i && tmp->fd_change == 0)
				tmp->fd_change++;
			if (tm_ou != tmp->out)
				tmp->fd_change += 2;
		}
		tmp = tmp->next;
	}
	return (SUCCESS);
}

int	execution(t_command *cmd, t_env **env, t_shell *shell)
{
	dup2(cmd->in, 0);
	dup2(cmd->out, 1);
	if (cmd->cmd && is_a_biltin(cmd->cmd) && !cmd->next && cmd->cmd_id == 0
		&& cmd->fd_change >= 0)
		return (ft_biltin(cmd, env, shell));
	fork_and_ecseve(shell, cmd);
	return (SUCCESS);
}

int	execute_cmd(t_shell *shell)
{
	t_command *cmd;
	int status;
	int tm_in;
	int tm_out;

	cmd = (*shell->cmd_info);
	tm_in = dup(0);
	tm_out = dup(1);
	if (!(cmd->next) && cmd->cmd && ft_strncmp(cmd->cmd[0], "exit", 5) == 0)
	{
		if (exit_path(cmd, shell, 1) == 1)
			return (tm_close(tm_in, tm_out, 0), ERROR);
	}
	make_redir(shell, cmd);
	//print_shell_info(shell);// qui possiamo gestire il -2
	while (cmd)
	{
		if (execution(cmd, shell->env, shell) == ERROR)
			return (tm_close(tm_in, tm_out, 1), ERROR);
		cmd = cmd->next;
	}
	while (waitpid(-1, &status, 0) > 0)
		if (WIFEXITED(status))
			g_status_code = WEXITSTATUS(status);
	return (tm_close(tm_in, tm_out, 1), SUCCESS);
}
