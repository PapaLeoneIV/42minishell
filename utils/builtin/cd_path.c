/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_path.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgori <fgori@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 19:07:02 by fgori             #+#    #+#             */
/*   Updated: 2024/07/01 19:11:07 by fgori            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	cd_excanger(char *new, char *path, t_env **env)
{
	t_env	*tmp;
	char	*sup;
	char	*sup_2;

	tmp = find_node(env, path);
	if (tmp == NULL)
	{
		sup = ft_strjoin(path, "=");
		sup_2 = ft_strjoin(sup, new);
		free(sup);
		add_node_to_env_struct(env, lst_new_env(sup_2, tmp->env_mtx));
		free(sup_2);
		return ;
	}
	free(tmp->body);
	tmp->body = ft_strdup(new);
	free(new);
}

static int	cd_rows(int mtx_rows, char **mtx, t_env **env)
{
	t_env	*tmp;
	int		result;

	if (mtx_rows == 2)
		result = chdir(mtx[1]);
	if (mtx_rows == 1)
	{
		tmp = find_node(env, "HOME");
		if (tmp == NULL)
		{
			write_exit("bash: ", "HOME", " Not set\n");
			return (1);
		}
		result = chdir(tmp->body);
	}
	if (result == -1)
	{
		write_exit("bash: ", mtx[1], ": No such file or directory\n");
		g_status_code = 1;
		return (1);
	}
	return (0);
}

int	cd_path(char **mtx, t_env **env)
{
	char	*old;
	char	*new;
	int		mtx_rows;

	mtx_rows = mtx_count_rows(mtx);
	if (mtx_rows > 2)
	{
		write(2, "bash: cd: too many arguments\n", 30);
		return (1);
	}
	old = getcwd(NULL, 0);
	if (cd_rows(mtx_rows, mtx, env) == 1)
	{
		free(old);
		return (1);
	}
	new = getcwd(NULL, 0);
	cd_excanger(old, "OLDPWD", env);
	cd_excanger(new, "PWD", env);
	return (0);
}
