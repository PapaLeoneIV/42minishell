/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_analizer.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rileone <rileone@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/11 10:36:07 by rileone           #+#    #+#             */
/*   Updated: 2024/05/17 13:37:27 by rileone          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/lexer.h"
void change_non_special_tokens_to_word_tokens(t_token *head)
{
	t_token *ptr;

	ptr = head;
	while(ptr)
	{
		if (ptr->type == DOLLAR_TOKEN 
		|| ptr->type == SING_QUOTES_TOKEN 
		|| ptr->type == DOUBLE_QUOTES_TOKEN) 
			ptr->type = WORD_TOKEN;
		ptr = ptr->next;
	}
}

int syntax_error_handler(t_token *head)
{
    t_token *ptr;

    ptr = head;
    if (check_for_non_valid_char_list(ptr, "{}();\\&*") == 1)
       return 0;
    change_non_special_tokens_to_word_tokens(head);
    while(ptr)
    {
        if (ptr->type == PIPE_TOKEN)
        {
            if (handle_pipe_synt_error_tokens(ptr) == 0)
            {
                printf("Syntax error near unexpected token '|'\n");
                return (0);
            }
        }
         else if (ptr->type == GREATER_TOKEN)
        {
            if (handle_greater_synt_error_tokens(ptr) == 0)
            {
                printf("Syntax error near unexpected token '>'\n");
                return (0);
            }    
        }
        else if (ptr->type == LESSER_TOKEN)
        {
            if (handle_lesser_synt_error_tokens(ptr) == 0)
            {
                printf("Syntax error near unexpected token '<'\n");
                return (0);
            }   
        }    
        ptr = ptr->next;
    }
    return 1;
}

