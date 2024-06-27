/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_maker.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgori <fgori@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 11:20:59 by fgori             #+#    #+#             */
/*   Updated: 2024/06/27 12:10:46 by fgori            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	make_things(t_command *cmd, t_env *path, t_env **env, t_shell *shell)
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
				return (freeall(open_path), freeall(tmp_env), clean_all(shell, 1), ERROR);
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
			return (ERROR);
		}
		free(supp);
	}
	clean_all(shell, 1);
	return (ERROR);
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
	{
		write(2, "bash: ", 7);
		write(2, cmd->cmd[0], ft_strlen(cmd->cmd[0]));
		write(2, ": No such file or directory\n", 29);
	}
	else if (cmd->fd_change >= 0)
	{
		if (make_things(cmd, tmp, shell->env, shell) == ERROR)
			//printf("status = %d", g_status_code)
			;
	}
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
		if (red_st == ERROR || red_st == -2)
		{
			g_status_code = 1;
			tmp->fd_change = -1;
			if (red_st == -2)
				return (ERROR);
		}
		else
		{
			if (tmp->in != tm_i && tmp->in == 0)
				tmp->fd_change++;
			if (tm_ou != tmp->out)
				tmp->fd_change += 2;
		}
		tmp = tmp->next;
	}
	return (SUCCESS);
}



void print_redir(t_redir *redir) {
    while (redir) {
        printf("Redirection:\n");
        printf("  In FD: \033[1;31m%d\033[0m\n", redir->in);  // Red for file descriptors
        printf("  Out FD: \033[1;31m%d\033[0m\n", redir->out);
        printf("  Type of Redirection: %d\n", redir->type_of_redirection);
        printf("  Heredoc Expansion: %d\n", redir->heredoc_expansion);
        printf("  Filename: %s\n", redir->filename ? redir->filename : "NULL");
        redir = redir->next;
    }
}

void print_command(t_command *cmd) {
    while (cmd) {
        printf("Command:\n");
        if (cmd->cmd) {
            printf("  Arguments:\n");
            for (int i = 0; cmd->cmd[i] != NULL; i++) {
                printf("    %s\n", cmd->cmd[i]);
            }
        }

        if (cmd->redirection_info && *cmd->redirection_info) {
            print_redir(*cmd->redirection_info);
        }

        printf("  Pipe IN: \033[1;31m%d\033[0m, Pipe OUT: \033[1;31m%d\033[0m\n", cmd->pip[0], cmd->pip[1]);
        printf("  Standard IN: \033[1;31m%d\033[0m\n", cmd->in);
        printf("  Standard OUT: \033[1;31m%d\033[0m\n", cmd->out);
        printf("  FD Change: %d\n", cmd->fd_change);
        printf("  Heredoc Content: %s\n", cmd->here ? cmd->here : "NULL");
        printf("  Command ID: %d\n", cmd->cmd_id);
        printf("  Fork ID: %d\n", cmd->fork_id);
        cmd = cmd->next;
    }
}
// da lavorare non completa!!!!!
int	execution(t_command *cmd, t_env **env, t_shell *shell)
{
	dup2(cmd->in, 0);
	dup2(cmd->out, 1);
	if (cmd->cmd && is_a_biltin(cmd->cmd) && !cmd->next && cmd->cmd_id == 0 && cmd->fd_change >= 0)
		return (ft_biltin(cmd, env, shell));
	fork_and_ecseve(shell, cmd);
	return (SUCCESS);
}


int	execute_cmd(t_shell *shell)
{
	t_command	*cmd;
	int			status;
	int			tm_in;
	int			tm_out;

	cmd = (*shell->cmd_info);
	tm_in = dup(0);
	tm_out = dup(1);
	if (!(cmd->next) && cmd->cmd && ft_strncmp(cmd->cmd[0],
			"exit", 5) == 0)
	{
		tm_close(tm_in, tm_out, 0);
		if (exit_path(cmd, shell) == 1)
			return (ERROR);
	}
	make_redir(shell, cmd);
	while (cmd)
	{
		//print_command(cmd);
		if (execution(cmd, shell->env, shell) == ERROR)
			return (tm_close(tm_in, tm_out, 1), ERROR);
		cmd = cmd->next;
	}
	while (waitpid(-1, &status, 0) > 0)
		if (WIFEXITED(status))
			g_status_code = WEXITSTATUS(status);
	return (tm_close(tm_in, tm_out, 1), SUCCESS);
}
