/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_builtin.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgori <fgori@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 15:03:45 by fgori             #+#    #+#             */
/*   Updated: 2024/07/08 19:14:53 by fgori            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_biltin(t_command *cmd, t_env **lst, t_shell *shell)
{
	int		built_exit_status;
	char	**tmp;

	built_exit_status = -1;
	tmp = cmd->cmd;
	if (ft_strncmp(tmp[0], "cd", 3) == 0)
		built_exit_status = cd_path(tmp, lst);
	else if (ft_strncmp(tmp[0], "pwd", 4) == 0)
		built_exit_status = pwd_path();
	else if (ft_strncmp(tmp[0], "echo", 5) == 0)
		built_exit_status = echo_path(tmp);
	else if (ft_strncmp(tmp[0], "env", 4) == 0)
		built_exit_status = env_path(lst);
	else if (ft_strncmp(tmp[0], "export", 7) == 0)
		built_exit_status = export_path(lst, tmp);
	else if (ft_strncmp(tmp[0], "unset", 6) == 0)
		built_exit_status = unset_path(lst, tmp);
	else if (ft_strncmp(tmp[0], "exit", 5) == 0)
		built_exit_status = exit_path(cmd, shell, 1);
	if (built_exit_status > -1)
		shell->status = built_exit_status;
	return (built_exit_status);
}

int	is_a_biltin(char **tmp)
{
	if (ft_strncmp(tmp[0], "cd", 3) == 0 || ft_strncmp(tmp[0], "pwd", 4) == 0
		|| ft_strncmp(tmp[0], "echo", 5) == 0 || ft_strncmp(tmp[0], "env",
			4) == 0 || ft_strncmp(tmp[0], "export", 7) == 0
		|| ft_strncmp(tmp[0], "unset", 6) == 0 || ft_strncmp(tmp[0], "exit",
			5) == 0)
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
		return (ft_strdup(cmd));
	while (open_path[i])
	{
		tmp = ft_strjoin(open_path[i], "/");
		supp = ft_strjoin(tmp, cmd);
		free(tmp);
		if (access(supp, F_OK) == 0)
			return (supp);
		free(supp);
		i++;
	}
	return (NULL);
}

char	*take_path(t_env *path, char **tmp_cmd, t_command *cmd, t_shell *shell)
{
	char	*supp;
	char	**open_path;

	if (path)
	{
		open_path = ft_split(path->body, ':');
		supp = ft_access(open_path, tmp_cmd[0]);
		if (!supp)
		{
			shell->status = 127;
			freeall(open_path);
			perror("ERROR\nunfinded path");
			return (NULL);
		}
		freeall(open_path);
		return (supp);
	}
	else
		return (ft_strdup(cmd->cmd[0]));
}

void	exev_error(t_shell *shell, char *supp)
{
	if (g_status_code == 130)
		shell->status = 130;
	else
	{
		shell->status = 126;
		write_exit("bash :", supp, "permession denied\n");
	}
}
