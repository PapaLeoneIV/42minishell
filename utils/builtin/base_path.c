/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   base_path.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rileone <rileone@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 16:21:45 by fgori             #+#    #+#             */
/*   Updated: 2024/05/23 20:06:14 by rileone          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//cd comand funtion//
void	cd_path(char **mtx)
{
	if (mtx_count_rows(mtx) > 2)
	{
		perror("ERROR\ntoo many arguments");
		return ;
	}
	chdir(mtx[1]);
}

void	pwd_path(void)
{
	char	*path;

	path = getcwd(NULL, 0);
	printf("%s\n", path);
	free(path);
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

void	echo_path(char **str)
{
	int		i;
	short	n_flag;

	i = 1;
	n_flag = true;
	/*qui bisogna assicurarsi che str[1] esista altrimenti andiamo in SEGFAULT*/
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
	if (!n_flag)
		printf("\n");
	free(str);
	return ;
}

void	env_path(t_env	**env)
{
	t_env	*tmp;

	tmp = (*env);
	while (tmp)
	{
		if (tmp->esistence == 0)
			printf("%s=%s\n", tmp->head, tmp->body);
		tmp = tmp->next;
	}
}
//cd comand funtion end//
