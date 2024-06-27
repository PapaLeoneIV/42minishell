/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_manipulating.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rileone <rileone@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 12:12:07 by fgori             #+#    #+#             */
/*   Updated: 2024/06/26 17:55:51 by rileone          ###   ########.fr       */
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
        write(2, "bash: export: `", 16);
		write(2, str, ft_strlen(str));
		write(2, ": No such file or directory\n", 29);
		return (0);
	}
	if (ft_isdigit(str[0]))
    {
        write(2, "bash: export: `", 16);
		write(2, str, ft_strlen(str));
		write(2, ": No such file or directory\n", 29);
        return (0);
    }
	while (str[i] != '\0' && str[i] != '='
		&& !(str[i] == '+' && str[i + 1] == '='))
	{
		if (!ft_isalnum(str[i]) && str[i] != '_')
        {
            write(2, "bash: export: `", 16);
		    write(2, str, ft_strlen(str));
		    write(2, ": No such file or directory\n", 29);
            return (0);
        }
		i++;
	}
	return (1);
}


int unset_path(t_env **lst, char **mtx)
{
    t_env   *tmp;
    int     i;
    int arg;
    arg = 1;
    i = 0;
    if (!mtx[1])
        return (0);
    while(mtx[arg])
    {
        if (ft_isdigit(mtx[arg][0]))
        {
            write(2, "bash: unset: not a valid identifier\n", 37);
            g_status_code = 1;
            return (1);
        }
        tmp = find_node(lst, mtx[arg]);
        if (!tmp)
        {
            arg++;
            continue ;
        }
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
        arg++;
    }
    return (0);
}
