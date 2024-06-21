/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_manipulating.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rileone <rileone@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 12:12:07 by fgori             #+#    #+#             */
/*   Updated: 2024/06/21 14:48:25 by rileone          ###   ########.fr       */
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
	while (str[i] != '\0' && str[i] != '='
		&& !(str[i] == '+' && str[i + 1] == '='))
	{
		if (!ft_isalnum(str[i]) && str[i] != '_')
			return (perror("invalid character in variable name\n"), 0);
		i++;
	}
	return (1);
}

int	unset_path(t_env **lst, char **mtx)
{
	t_env	*tmp;

	if (!mtx[1])
	{
		perror("ERROR\n");
		return (2);
	}
	tmp = find_node(lst, mtx[1]);
	if (!tmp)
	{
		perror("ERROR\n");
		return (2);
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
	return (0);
}
