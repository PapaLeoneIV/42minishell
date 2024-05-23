/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rileone <rileone@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/21 14:02:41 by rileone           #+#    #+#             */
/*   Updated: 2024/05/23 18:24:54 by rileone          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/***per il momento:
 * - se un token e' di tipo double quotes, ma e' preceduto da unn HEREDOC viene marchiato come HEREDOC_FILENAME_WITHQUOTES
 * - ho deciso di non mantenere le doppie virgolette, in quanto se seguito da qualcosa quando viene joinato si creano dei problemi
 * 			si crea qualcosa di tipo es: << "here"doc ====> diventa un token->value "here"doc e non heredoc invece
 * - se HEREDOC_FILENAME_WITHQUOTES deve essere joinato con altre cose perche non c'e' spazio tra i token 
 * 			mantiene comquneue il suo tokenTYPE HEREDOC_FILENAME_WITHQUOTES
 * 
 * 
*/

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