/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   base_path.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgori <fgori@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 16:21:45 by fgori             #+#    #+#             */
/*   Updated: 2024/07/16 14:37:00 by fgori            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	pwd_path(void)
{
	char	*path;

	path = getcwd(NULL, 0);
	ft_printf("%s\n", path);
	free(path);
	return (0);
}

static int	check_n_flag(char *str, short *n_flag, int *pos, int stop)
{
	int			i;

	i = 1;
	if (ft_strncmp(str, "-n", 2) == 0 && !stop)
	{
		while (str[i] != '\0')
		{
			if (str[i] != 'n')
			{
				return (1);
			}
			i++;
		}
		*n_flag = false;
		*pos += 1;
		return (0);
	}
	return (1);
}

int	echo_path(char **str)
{
	int		i;
	short	n_flag;
	int		stop;

	i = 1;
	stop = 0;
	n_flag = true;
	if (!str)
		return (2);
	if (mtx_count_rows(str) > 1)
	{
		while (str[i] != NULL)
		{
			if (check_n_flag(str[i], &n_flag, &i, stop) == 1 && ++stop)
			{
				ft_printf("%s", str[i]);
				if (str[i + 1])
					ft_printf(" ");
				i++;
			}
		}
	}
	if (n_flag)
		ft_printf("\n");
	return (0);
}

int	env_path(t_env **env, t_command *cmd)
{
	t_env	*tmp;

	tmp = (*env);
	while (tmp)
	{
		if (mtx_count_rows(cmd->cmd) > 1)
		{
			write_exit(cmd->cmd[1], " : No such file or directory\n", NULL);
			return (127);
		}
		if (tmp->esistence <= 0)
			ft_printf("%s=%s\n", tmp->head, tmp->body);
		tmp = tmp->next;
	}
	return (0);
}
