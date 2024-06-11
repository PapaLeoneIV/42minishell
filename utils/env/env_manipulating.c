/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_manipulating.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgori <fgori@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 12:12:07 by fgori             #+#    #+#             */
/*   Updated: 2024/06/11 11:14:43 by fgori            ###   ########.fr       */
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
	if (ft_isdigit(str[0]))
		return (perror("number in top of variable"), 0);
	while (str[i] != '\0' && str[i] != '=' && !(str[i] == '+' && str[i + 1] == '='))
	{
		if (!ft_isalnum(str[i]) && str[i] != '_')
			return (perror("invalid character in variable name\n"), 0);
		i++;
	}
	return(1);
}

void	normal_equal(t_env **lst, char *str)
{
	char	*sup;
	t_env	*tmp;

	sup = ft_substr(str, 0, ft_strchri(str, '='));
	tmp = find_node(lst, sup);
	if (!tmp)
		add_node_to_env_struct(lst, lst_new_env(str, (*lst)->env_mtx));
	else
	{
		free(tmp->body);
		tmp->body = ft_substr(str, ft_strchri(str, '=') + 1, ft_strlen(str));
	}
	free(sup);
}

int	export_path(t_env **lst, char **mtx)
{
	t_env	*tmp;
	char	*sup;
	int i;

	i = 1;
	if (mtx_count_rows(mtx) == 1)
		solo_export(lst);
	while (mtx[i] && check_head(mtx[i]))
	{
		if (ft_strnstr(mtx[i], "+=", ft_strlen(mtx[i])))
		{
			sup =  ft_substr(mtx[i], 0, ft_strchri(mtx[i], '+'));
			tmp = find_node(lst, sup);
			free(sup);
			if (!tmp)
				add_node_to_env_struct(lst, lst_new_env(mtx[i], (*lst)->env_mtx));
			tmp->body = ft_strjoin(tmp->body, ft_substr(mtx[i], ft_strchri(mtx[i], '=') + 1 , ft_strlen(mtx[i])));
			if (tmp->esistence == 1)
				tmp->esistence = 0;
		}
		else
			normal_equal(lst, mtx[i]);
		i++;
	}
	return ((mtx[i] == NULL));
}

int	unset_path(t_env **lst, char **mtx)
{
	t_env	*tmp;

	if (!mtx[1])
	{
		perror("ERROR\n");
		return (0);
	}
	tmp = find_node(lst, mtx[1]);
	if (!tmp)
	{
		perror("ERROR\n");
		return (0);
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
