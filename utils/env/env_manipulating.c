/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_manipulating.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rileone <rileone@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 12:12:07 by fgori             #+#    #+#             */
/*   Updated: 2024/07/04 13:41:52 by rileone          ###   ########.fr       */
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

void	write_exit(char *str, char *cmd, char *finish)
{
	write(2, str, ft_strlen(str));
	write(2, cmd, ft_strlen(cmd));
	write(2, finish, ft_strlen(finish));
}

int	check_head(char *str)
{
	int	i;

	i = 1;
	if (ft_strchri(str, '=') == 0)
	{
		write_exit("bash: export: `", str, ": No such file or directory\n");
		return (0);
	}
	if (ft_isdigit(str[0]))
	{
		write_exit("bash: export: `", str, ": No such file or directory\n");
		return (0);
	}
	while (str[i] != '\0' && str[i] != '=' && !(str[i] == '+' && str[i
				+ 1] == '='))
	{
		if (!ft_isalnum(str[i]) && str[i] != '_')
		{
			write_exit("bash: export: `", str, ": No such file or directory\n");
			return (0);
		}
		i++;
	}
	return (1);
}

void	correct_and_clean(t_env *tmp, t_env **lst)
{
	if (!tmp->prev)
	{
		tmp->next->prev = NULL;
		(*lst) = tmp->next;
		clean_env_node(&tmp);
	}
	else if (!tmp->next)
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

int	unset_path(t_env **lst, char **mtx)
{
	t_env	*tmp;
	int		arg;

	arg = 1;
	if (!mtx[1])
		return (0);
	while (mtx[arg])
	{
		if (ft_isdigit(mtx[arg][0]))
		{
			write(2, "bash: unset: not a valid identifier\n", 37);
			return (1);
		}
		tmp = find_node(lst, mtx[arg]);
		if (!tmp)
		{
			arg++;
			continue ;
		}
		correct_and_clean(tmp, lst);
		arg++;
	}
	return (0);
}
