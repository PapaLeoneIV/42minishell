/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   base_path.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rileone <rileone@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 16:21:45 by fgori             #+#    #+#             */
/*   Updated: 2024/06/25 10:37:46 by rileone          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//cd comand funtion//

void	cd_excanger(char *new, char *path, t_env **env)
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

int	cd_path(char **mtx, t_env **env)
{
	char	*old;
	char	*new;
	int		mtx_rows;
	int		result;
	t_env	*tmp;

	mtx_rows = mtx_count_rows(mtx);
	if (mtx_rows > 2)
	{
		write(2, "\ntoo many arguments", 20);
		return (1);
	}
	
	old = getcwd(NULL, 0);
	if (mtx_rows == 2)
		result = chdir(mtx[1]);
	if (mtx_rows == 1)
	{
		tmp = find_node(env, "HOME");
		result = chdir(tmp->body);
	}
	new = getcwd(NULL, 0);
	if (result == -1)
	{
		g_status_code = 1;
		free(old);
		free(new);
		return (1);
	}
	cd_excanger(old, "OLDPWD", env);
	cd_excanger(new, "PWD", env);
	return (0);
}

int	pwd_path(void)
{
	char	*path;

	path = getcwd(NULL, 0);
	printf("%s\n", path);
	free(path);
	return (0);
}

int	echo_path(char **str)
{
	int		i;
	short	n_flag;

	i = 1;
	n_flag = true;
	if (!str)
		return (2);
	if (mtx_count_rows(str) > 1)
	{
		if (ft_strncmp(str[1], "-n", ft_strlen(str[1])) == 0)
		{
			i++;
			n_flag = false;
		}
		while (str[i])
		{
			printf("%s", str[i]);
			if (str[i + 1])
				printf(" ");
			i++;
		}
	}
	if (n_flag)
		printf("\n");
	return (0);
}

int	env_path(t_env	**env)
{
	t_env	*tmp;

	tmp = (*env);
	while (tmp)
	{
		if (tmp->esistence <= 0)
			printf("%s=%s\n", tmp->head, tmp->body);
		tmp = tmp->next;
	}
	return (0);
}
//cd comand funtion end//
