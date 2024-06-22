/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rileone <rileone@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/21 14:02:41 by rileone           #+#    #+#             */
/*   Updated: 2024/06/22 14:18:41 by rileone          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
int g_status_code;


int	main(int argc, char **argv , char **envp)
{
	g_status_code = 0;

	t_shell	shell;
	shell = (t_shell){0};
	(void)argv;
	if (argc != 1)
	{
		perror("Wrong number of arguments my boi!");
		/*qui bisogna capire cosa vogliamo fare quando */
	}
	read_from_stdin(&shell, envp);
	return (EXIT_SUCCESS);
}