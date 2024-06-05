/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   base_path.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgori <fgori@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 16:21:45 by fgori             #+#    #+#             */
/*   Updated: 2024/06/05 17:34:44 by fgori            ###   ########.fr       */
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
	if (!tmp)
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
	
	if (mtx_count_rows(mtx) < 2)
	{
		perror("ERROR\ntoo many arguments");
		return (-1);
	}
	old = getcwd(NULL, 0);
	chdir(mtx[1]);
	new = getcwd(NULL, 0);
	cd_excanger(old, "OLDPWD", env);
	cd_excanger(new, "PWD", env);
	return (1);
}

int	pwd_path(t_env **env)
{
	t_env	*path;

	path = find_node(env, "PWD");
	printf("%s\n", path->body);
	free(path);
	return (1);
}

char	*trimming(char *big, char *removed)
{
	int	i;

	i = 0;
	while (removed[i])
		i++;
	//if (!removed[i])
	//	return (NULL);
	i++;
	return(&big[i]);
}

int	echo_path(char **str)
{
	int		i;
	short	n_flag;

	i = 1;
	n_flag = true;
	if (!str)
		return (-1);
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
/* 	free(str); */
	return (1);
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
	return (1);
}
//cd comand funtion end//
