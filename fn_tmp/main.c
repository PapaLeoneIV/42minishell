/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rileone <rileone@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 10:30:26 by fgori             #+#    #+#             */
/*   Updated: 2024/05/22 22:18:54 by rileone          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	make_ban(void)
{
	int	i;

	i = 0;
	while (i++ < 5)
		putchar('\n');
	printf("/--\\  /--\\  |--|  |\\   |--|  |--|  /----\\  |--|   |--|   |------|  |--|\n");
	printf("|   \\/   |  |  |  | \\  |  |  |  |  \\   ||  |  |   |  |   |  |      |  |\n");
	printf("|        |  |  |  |  \\ |  |  |  |    \\     |  -----  |   |  --|    |  |\n");
	printf("|  |\\/|  |  |  |  |  |\\   |  |  |  ||  \\   |  |   |  |   |  |      |  |\n");
	printf("|--|  |--|  |--|  |--| |--|  |--|  \\----/  |--|   |--|   |------|  |-------|\n");
	while (i-- > 0)
		putchar('\n');
}

void	make_cmd(char *tmp, t_env **lst)
{
	/**io direi di aspettare perche credo che invece
	 * di passarci una stringa bisogna passarci il nodo_cmd
	*/
	if (ft_strncmp(tmp, "cd", 2) == 0)
	{
		cd_path(tmp);
	}
	else if (ft_strncmp(tmp, "pwd", 3) == 0)
	{
		pwd_path();
	}
	else if (ft_strncmp(tmp, "echo", 4) == 0)
		echo_path(tmp);
	else if (ft_strncmp(tmp, "env", 3) == 0)
		env_path(lst);
	else if (ft_strncmp(tmp, "export", 6) == 0)
		export_path(lst, tmp);
	else if (ft_strncmp(tmp, "unset", 5) == 0)
		unset_path(lst, tmp);
	free(tmp);
	//analise_cmd(str, lst); 
	return ;
}

void	make_shel(t_env **lst)
{
	char	*line;
	char	*support;
	
	while (1)
	{
		support = path();
		line = readline(support);
		add_history(line);
		tmp = ft_strtrim(line, " 	");
		if (ft_strncmp(tmp, "exit", 4) == 0)
		{
			free(tmp);	
			break ;
		}	
		make_cmd(t_shell->cmd_info, lst);
		free(support);
	}
	support = NULL;
}

int	main(int ac, char *av[], char *env[])
{
	t_env	**lst;

	if (ac != 1)
	{
		perror("to much input");
		exit(1);
	}
	(void)av;
	make_ban();
	lst = to_env_to_list(env);
	make_shel(lst);
	clean_env_lst(lst);
	return (0);
}
