/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_helpers.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rileone <rileone@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 16:23:54 by fgori             #+#    #+#             */
/*   Updated: 2024/05/22 22:39:12 by rileone          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_env	*ft_lstlast_(t_env *lst)
{
	while (lst && lst-> next != NULL)
		lst = lst->next;
	return (lst);
}

void	add_node_to_env_struct(t_env **env_list, t_env *new)
{
	t_env	*temp;

	if (!*env_list)
	{
		*env_list = new;
		return ;
	}
	if (!new)
		return ;
	temp = ft_lstlast_(*env_list);
	temp->next = new;
	new->prev = temp;
	new->next = NULL;
}

t_env	*lst_new_env(char *envp_line, char **en)
{
	t_env	*new;
	int 	envp_equal_idx;

	new = ft_calloc(1, sizeof(t_env));
	if (!new)
		return (NULL);
	envp_equal_idx = ft_strchri(envp_line, '=');
	if (!envp_line)
	{
		new->head = NULL;
		new->body = NULL;
	}
	if (envp_equal_idx != -1)
	{
		new->head = ft_substr(envp_line, 0, envp_equal_idx);
		new->body = ft_substr(envp_line, envp_equal_idx + 1, ft_strlen(envp_line));
		new->esistence = 0;
	}
	else
	{
		new->head = ft_strdup(envp_line);
		new->esistence = 1;
	}
	new->env = en;
	new->next = NULL;
	return (new);
}

t_env	**get_env_info(char *envp_mtx[])
{
	t_env	**env_struct;
	t_env	*node;
	int		counter;

	counter = 0;
	env_struct = ft_calloc(1, sizeof(t_env *));
	while (envp_mtx[counter])
	{
		node = lst_new_env(envp_mtx[counter], envp_mtx);
		/**qui sei viene ritornato null bisogna gestirlo */
		add_node_to_env_struct(env_struct, node);
		counter++;
	}
	return (env_struct);
}