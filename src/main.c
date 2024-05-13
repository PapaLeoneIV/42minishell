/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rileone <rileone@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/21 14:02:41 by rileone           #+#    #+#             */
/*   Updated: 2024/05/13 16:50:50 by rileone          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int main(int argc, char **argv , char **envp)
{
    t_shell shell;
    
    shell = (t_shell){0};
    shell.envp = envp; 
    (void)argv;
    if(argc != 1)
        perror("numero di argomenti sbagliato!");
    read_from_stdin(&shell);
/*     set_env(&shell, envp); */
    return (0);
}