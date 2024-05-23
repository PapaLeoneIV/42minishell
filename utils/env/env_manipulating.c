/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_manipulating.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rileone <rileone@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 12:12:07 by fgori             #+#    #+#             */
/*   Updated: 2024/05/22 22:05:50 by rileone          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_env	*find_node(t_env **lst, char *str)
{
	t_env	*tmp;

	tmp = (*lst);
	while (tmp)
	{
		if (ft_strncmp(tmp->head, str, ft_strlen(str)) == 0)
			return (tmp);
		tmp = tmp->next;
	}
	return (NULL);
}

void	export_path(t_env **lst, char **mtx)
{
	t_env	*tmp;
	int i;

	i = 1;
	if (mtx_count_rows(mtx) == 1)
	{
		tmp = (*lst);
		while (tmp)
		{
			printf("declare -x %s=%s\n", tmp->head, tmp->body);
			tmp = tmp->next;
		}
		return ;
	}
	while (mtx[i])
	{
		if (ft_strnstr(mtx[i], "+=", ft_strlen(mtx[i])))
		{
			mtx[i] = trimming(mtx[i], "export");
			tmp = find_node(lst, ft_substr(mtx[i], 0, ft_strchri(mtx[i], '+')));
			if (!tmp)
				add_node_to_env_struct(lst, lst_new_env(mtx[i], (*lst)->env_mtx));
			tmp->body = ft_strjoin(tmp->body, ft_substr(mtx[i], ft_strchri(mtx[i], '=') + 1 , ft_strlen(mtx[i])));
		}
		else
		{
			mtx[i] = trimming(mtx[i], "export");
			add_node_to_env_struct(lst, lst_new_env(mtx[i], (*lst)->env_mtx));
			//free(str);
		}
		i++;
	}
}

void	unset_path(t_env **lst, char **mtx)
{
	t_env	*tmp;

	if (!mtx[0])
	{
		perror("ERROR\n");
		return ;
	}
	tmp = find_node(lst, mtx[0]);
	if (!tmp)
	{
		perror("ERROR\n");
		return ;
	}
	if (!tmp->next)
	{
		tmp->prev->next = NULL;
		clean_env_node(&tmp);
	}
	else
	{
		tmp->prev->next = tmp->next;
		tmp->next->prev = tmp->prev;
		clean_env_node(&tmp);
	}

}
