/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_maker.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgori <fgori@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 17:55:26 by fgori             #+#    #+#             */
/*   Updated: 2024/06/24 19:10:55 by fgori            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	make_things(char **cmd, t_env *path, t_env **env, t_shell *shell)
{
	char	**open_path;
	char	*supp;
	char	**tmp_cmd;
	char	**tmp_env;


	if (ft_biltin(cmd, env, shell) == -1)
	{
		tmp_cmd = mtx_dup(cmd, mtx_count_rows(cmd));
		tmp_env = mtx_dup(path->env_mtx, mtx_count_rows(path->env_mtx));
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
		clean_all(shell, 1);
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
		if (execve(supp, tmp_cmd, tmp_env) < 0)
		{
			g_status_code = 126;
			return (perror("ERROR\nexecve don't replies"), ERROR);
		}
		free(supp);
	}
	clean_all(shell, 1);
	return (ERROR);
}

void	child_process(t_shell *shell, t_command *cmd, int tm_i, int tm_ou)
{
	t_env	*tmp;

	if (cmd->in != tm_i)
	{
		dup2(cmd->in, 0);
		close(cmd->in);
	}
	if (cmd->out != tm_ou)
	{
		dup2(cmd->out, 1);
		close(cmd->out);
	}
	tmp = find_node(shell->env, "PATH");
	if (tmp == NULL && access(cmd->cmd[0], F_OK) != 0)
	{
		perror("unvalid Path\n");
		clean_all(shell, 1);
	}
	else
	{
		if (make_things(cmd->cmd, tmp, shell->env, shell) == ERROR)
		{
			printf("status = %d", g_status_code);
			//clean_all(shell, 1);
		}
	}
	exit(g_status_code);
}

void	fork_and_ecseve(t_shell *shell, t_command *cmd, int tm_i, int tm_ou)
{
	if (cmd->cmd)
		cmd->fork_id = fork();
	if (cmd->fork_id == 0)
	{
		if (cmd->next)
			close(cmd->pip[0]);
		if (cmd->prev)
			close(cmd->pip[1]);
		child_process(shell, cmd, tm_i, tm_ou);
	}
	else
	{
		if (cmd->here)
		{
			unlink(cmd->here);
		}
		if (cmd->in != 0)
			close(cmd->in);
		if (cmd->out != 1)
			close(cmd->out);
	}
}

// da lavorare non completa!!!!!
int	execution(t_command *cmd, t_env **env, t_shell *shell)
{
	int		tm_i;
	int		tm_ou;
	int		red_st;

	tm_i = cmd->in;
	tm_ou = cmd->out;
	if (set_pip(cmd, cmd->pip) == ERROR)
		return (ERROR);
	red_st = open_redir(cmd, shell);
	if (red_st == ERROR || red_st == -2)
	{
		g_status_code = 1;
		if (red_st == -2)
			return (ERROR);
		return (perror("ERROR file opening\n"), ERROR);
	}
	dup2(cmd->in, 0);
	dup2(cmd->out, 1);
	if (cmd->cmd && is_a_biltin(cmd->cmd) && !cmd->next && cmd->cmd_id == 0)
		return (ft_biltin(cmd->cmd, env, shell));
	fork_and_ecseve(shell, cmd, tm_i, tm_ou);
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
		if (exit_path(cmd, shell) == 300)
			return (ERROR);
	}	
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
