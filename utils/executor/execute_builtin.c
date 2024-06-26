/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_builtin.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rileone <rileone@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 15:03:45 by fgori             #+#    #+#             */
/*   Updated: 2024/06/26 17:16:53 by rileone          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_biltin(t_command *cmd, t_env **lst, t_shell *shell)
{
	int		i;
	char	**tmp;
	
	i = -1;
	tmp = cmd->cmd;
	if (ft_strncmp(tmp[0], "cd", ft_strlen(tmp[0])) == 0)
	{
		i = cd_path(tmp, lst);
	}
	else if (ft_strncmp(tmp[0], "pwd", ft_strlen(tmp[0])) == 0)
	{
		i = pwd_path();
	}
	else if (ft_strncmp(tmp[0], "echo", ft_strlen(tmp[0])) == 0)
		i = echo_path(tmp);
	else if (ft_strncmp(tmp[0], "env", ft_strlen(tmp[0])) == 0)
		i = env_path(lst);
	else if (ft_strncmp(tmp[0], "export", ft_strlen(tmp[0])) == 0)
		i = export_path(lst, tmp);
	else if (ft_strncmp(tmp[0], "unset", ft_strlen(tmp[0])) == 0)
		i = unset_path(lst, tmp);
	else if (ft_strncmp(tmp[0], "exit", ft_strlen(tmp[0])) == 0)
		i = exit_path(cmd , shell);
	if(g_status_code > -1)
		g_status_code = i;
	return (i);
}

int	is_a_biltin(char **tmp)
{
	if (ft_strncmp(tmp[0], "cd", ft_strlen(tmp[0])) == 0
		|| ft_strncmp(tmp[0], "pwd", ft_strlen(tmp[0])) == 0
		|| ft_strncmp(tmp[0], "echo", ft_strlen(tmp[0])) == 0
		|| ft_strncmp(tmp[0], "env", ft_strlen(tmp[0])) == 0
		|| ft_strncmp(tmp[0], "export", ft_strlen(tmp[0])) == 0
		|| ft_strncmp(tmp[0], "unset", ft_strlen(tmp[0])) == 0
		|| ft_strncmp(tmp[0], "exit", ft_strlen(tmp[0])) == 0)
		return (1);
	return (0);
}

char	*ft_access(char **open_path, char *cmd)
{
	char	*tmp;
	char	*supp;
	int		i;

	i = 0;
	if (access(cmd, F_OK) == 0)
		return (cmd);
	while (open_path[i])
	{
		tmp = ft_strjoin(open_path[i], "/");
		supp = ft_strjoin(tmp, cmd);
		free(tmp);
		if (access(supp, F_OK) == 0)
			return (supp);
		free (supp);
		i++;
	}
	return (NULL);
}
