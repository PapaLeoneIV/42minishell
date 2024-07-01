/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   base_path.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgori <fgori@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 16:21:45 by fgori             #+#    #+#             */
/*   Updated: 2024/07/01 19:07:17 by fgori            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

int	env_path(t_env **env)
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
