/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cat_exeption.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 23:02:54 by codespace         #+#    #+#             */
/*   Updated: 2024/07/03 06:49:59 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	write_line(int cat, t_shell *shell)
{
	char *line;

	while (cat > 0)
	{
		gnl2(&line);
		free(line);
		cat--;
	}
	clean_all(shell, 1);
}

int	cat_check(t_command *cmd)
{
	t_command	*tmp;
	int			i;

	tmp = cmd;
	i = 0;
	if (tmp->cmd_id == 0 && ft_strncmp(tmp->cmd[0], "cat", 4) == 0)
	{
		while (tmp && ft_strncmp(tmp->cmd[0], "cat", 4) == 0 && !cmd->redirection_info)
		{
			tmp->cat = 1;
			i++;
			tmp = tmp->next;
		}
	}
	return (i);
}
