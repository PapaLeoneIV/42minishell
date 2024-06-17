/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgori <fgori@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/21 14:02:41 by rileone           #+#    #+#             */
/*   Updated: 2024/06/12 16:29:19 by fgori            ###   ########.fr       */
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
    read_from_stdin(&shell, envp);
    return (0);
}

// il singolo ' comprime gli spazi nelle parentesi vedi echo '    dkjb    vhb    ', gli unici spazi a restare sono quelli fra due parole
//il programma rivela * come invalid caracter ma in funzione expr fa da moltiplicazione