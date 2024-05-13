/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_input.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rileone <rileone@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/21 17:12:07 by rileone           #+#    #+#             */
/*   Updated: 2024/05/13 16:24:46 by rileone          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "../../includes/lexer.h"


char *join_token_values(t_token *head)
{
    t_token *current;

    current = head;
    char *joined_values = malloc(1);
    joined_values[0] = '\0';
    while (current != NULL)
    {
        joined_values = ft_strjoin(joined_values, current->value);
        current = current->next;
    }
    return joined_values;
}

void read_from_stdin(t_shell *shell)
{
    t_token     *head;
    char*       input;
/*      char *      tmp_input;  */
    (void)shell;
    while (1)
    {
        input = readline("(MINISHELL)$");
        head = tokenize_input(input, shell);
        /*  if (head == NULL)
            continue; 
        tmp_input = join_token_values(head);
        if (syntax_error_handler(head, join_token_values(head)) == 0)
        {
            printf("Syntax error\n");
            continue;
        } */
        free(input);
    }
}