/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rileone <rileone@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/21 14:02:41 by rileone           #+#    #+#             */
/*   Updated: 2024/06/21 11:11:14 by rileone          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	main(int argc, char **argv , char **envp)
{
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