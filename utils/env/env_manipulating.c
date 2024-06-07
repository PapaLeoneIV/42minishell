/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_manipulating.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgori <fgori@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 12:12:07 by fgori             #+#    #+#             */
/*   Updated: 2024/06/07 14:29:56 by fgori            ###   ########.fr       */
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

void	solo_export(t_env **lst)
{
	t_env	*tmp;

	tmp = (*lst);
	while (tmp)
	{
		if (tmp->esistence > -1)
			printf("declare -x %s=%s\n", tmp->head, tmp->body);
		tmp = tmp->next;
	}
}

int	check_head(char *str)
{
	int	i;

	i = 1;
	if (ft_strchri(str, '=') == 0)
	{
		perror("invalid operetion\n");
		return (0);
	}
	if (ft_isdigit(str[i]))
		return (perror("number in top of variable"), 0);
	while (str[i] != '\0' && str[i] != '=')
	{
		if (!ft_isalnum(str[i]) && str[i] != '_')
			return (perror("invalid character in variable name\n"), 0);
		i++;
	}
	return(1);
}

int	export_path(t_env **lst, char **mtx)
{
	t_env	*tmp;
	int i;

	i = 1;
	if (mtx_count_rows(mtx) == 1)
		solo_export(lst);
	while (mtx[i] && check_head(mtx[i]))
	{
		if (ft_strnstr(mtx[i], "+=", ft_strlen(mtx[i])))
		{
			tmp = find_node(lst, ft_substr(mtx[i], 0, ft_strchri(mtx[i], '+')));
			if (!tmp)
				add_node_to_env_struct(lst, lst_new_env(mtx[i], (*lst)->env_mtx));
			tmp->body = ft_strjoin(tmp->body, ft_substr(mtx[i], ft_strchri(mtx[i], '=') + 1 , ft_strlen(mtx[i])));
			if (tmp->esistence == 1)
				tmp->esistence = 0;
		}
		else
			add_node_to_env_struct(lst, lst_new_env(mtx[i], (*lst)->env_mtx));
		i++;
		return (1);
	}
	return (-1);
}

int	unset_path(t_env **lst, char **mtx)
{
	t_env	*tmp;

	if (!mtx[1])
	{
		perror("ERROR\n");
		return (-1);
	}
	tmp = find_node(lst, mtx[1]);
	if (!tmp)
	{
		perror("ERROR\n");
		return (-1);
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
	return (1);
}
