/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_cleaner.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgori <fgori@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 10:51:30 by fgori             #+#    #+#             */
/*   Updated: 2024/07/02 10:43:07 by fgori            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	clean_env_node(t_env **lst)
{
	if ((*lst)->body)
		free((*lst)->body);
	if ((*lst)->head)
		free((*lst)->head);
	free(*lst);
}

void	clean_env_lst(t_env **lst)
{
	t_env	*tmp;

	while ((*lst))
	{
		tmp = (*lst)->next;
		clean_env_node(lst);
		*lst = tmp;
	}
	free(lst);
}

void	multi_freeall(char **tmp_env, char **tmp_cmd, t_shell *shell)
{
	if (tmp_env)
		freeall(tmp_env);
	if (tmp_cmd)
		freeall(tmp_cmd);
	if (shell)
		clean_all(shell, 1);
}
