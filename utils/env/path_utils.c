/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rileone <rileone@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 14:24:51 by rileone           #+#    #+#             */
/*   Updated: 2024/05/02 19:44:23 by rileone          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../../includes/lexer.h"


char *get_env_value(char **envp, char *env_var)
{
	int	i;

	i = 0;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], env_var, ft_strlen(env_var)) == 0)
			return (envp[i] + ft_strlen(env_var));
		i++;
	}
	return (NULL);
}



char **return_path_string_splitted(t_token **head, t_shell *shell)
{
	char 	*tmpcmd;
	char	**tmpmtx;
	int		i;
	(void)head;
	i = 0;
	tmpcmd = path_string(shell);
	if (!tmpcmd)
		return NULL;
	tmpmtx = ft_split(tmpcmd, ':');
	while(tmpmtx && tmpmtx[i])
	{
		tmpmtx[i] = ft_strjoinchar(tmpmtx[i], '/');
		i++;
	}
	return (tmpmtx);
}
