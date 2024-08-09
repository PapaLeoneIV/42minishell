/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_cleaner.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgori <fgori@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/31 12:03:40 by fgori             #+#    #+#             */
/*   Updated: 2024/07/18 10:54:52 by fgori            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	clean_redir(t_redir **redir)
{
	t_redir	*tmp;

	while ((*redir))
	{
		tmp = (*redir);
		free(tmp->filename);
		(*redir) = tmp->next;
		free(tmp);
	}
	free(redir);
}

void	clean_cmd_node(t_command **cmd)
{
	t_command	*tmp;
	struct stat	st;

	while ((*cmd))
	{
		tmp = (*cmd);
		if (tmp->in != -1 && (fstat(tmp->in, &st) == 0))
			close(tmp->in);
		if (tmp->out != -1 && (fstat(tmp->out, &st) == 0))
			close(tmp->out);
		if (tmp->pip[0] != 0 && (fstat(tmp->pip[0], &st) == 0))
			close(tmp->pip[0]);
		if (tmp->pip[1] != 0 && (fstat(tmp->pip[1], &st) == 0))
			close(tmp->pip[1]);
		if (tmp->save_rd[0] != 0 && (fstat(tmp->save_rd[0], &st) == 0))
			close(tmp->save_rd[0]);
		if (tmp->save_rd[1] != 0 && (fstat(tmp->save_rd[1], &st) == 0))
			close(tmp->save_rd[1]);
		freeall((*cmd)->cmd);
		if ((*cmd)->redirection_info)
			clean_redir((*cmd)->redirection_info);
		(*cmd) = (*cmd)->next;
		free(tmp);
	}
	free(cmd);
}

void	clean_all(t_shell *shell, int flag)
{
	if (flag)
	{
		clean_env_lst(shell->env);
		rl_cleanup_after_signal();
	}
	if (shell->line)
		free(shell->line);
	if (shell->cmd_info)
		clean_cmd_node(shell->cmd_info);
}

void	freeall(char **mat)
{
	int	n;

	n = 0;
	while (mat && mat[n])
	{
		free(mat[n]);
		mat[n] = NULL;
		n++;
	}
	free(mat);
}
