/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgori <fgori@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/21 14:02:41 by rileone           #+#    #+#             */
/*   Updated: 2024/05/24 11:09:36 by fgori            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int main(int argc, char **argv , char **envp)
{
    t_shell shell;
    
    shell = (t_shell){0}; 
    (void)argv;
    if(argc != 1)
        perror("Wrong number of arguments my boi!");
    shell.env = get_env_info(envp);
    read_from_stdin(&shell);
/*     set_env(&shell, envp); */
    return (0);
}

/* aggiunto -I./include al main, aggiunto prev a typedef struct s_command e aggiornato e relativo new_cmd
 */