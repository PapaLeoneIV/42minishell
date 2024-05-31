/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_cleaner.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgori <fgori@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/31 12:03:40 by fgori             #+#    #+#             */
/*   Updated: 2024/05/31 12:29:32 by fgori            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "lexer.h"

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
	t_command *tmp;

	while ((*cmd))
	{
		tmp = (*cmd);
		freeall((*cmd)->cmd);
		if ((*cmd)->redirection_info)
			clean_redir((*cmd)->redirection_info);
		(*cmd) = (*cmd)->next;
		free(tmp);
	}
	free(cmd);
	
}

void	clean_all(t_shell *shell)
{
	clean_env_lst(shell->env);
	if (shell->line)
		free(shell->line);
	if (shell->cmd_info)
		clean_cmd_node(shell->cmd_info);
}