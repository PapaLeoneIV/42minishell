/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rileone <rileone@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/21 14:24:49 by rileone           #+#    #+#             */
/*   Updated: 2024/04/24 17:54:24 by rileone          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"


/* void split_envp(t_shell *shell, char *envp)
{
	char *split;
	char *key;
	char *value;

	split = ft_strchr(envp, '=');
	if (!split)
	{
		key = ft_strdup(envp);
		value = NULL;
	}
	else
	{
		*split = 0;
		key = ft_strdup(envp);
		value = ft_strdup(split + 1);
	}
		(void)value;
		(void)key;
		(void)shell;
	devo creare delle funzioni specifiche per envp
	addNode(&(shell->envp), key, value);
} */

/* void set_env(t_shell *shell, char **envp)
{
	int envp_len;
	int counter;

	counter = 0;
	envp_len = mtx_count_rows(envp);
	shell->envp = NULL;
	while(counter < envp_len)
	{
		split_envp(shell, envp[counter]);
		counter++;
	}
	printDictionary(shell->envp);	
} */