/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_analizer.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rileone <rileone@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/11 10:36:07 by rileone           #+#    #+#             */
/*   Updated: 2024/05/21 17:57:11 by rileone          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/lexer.h"
/**Una volta aver tokenizzato ed espanso le variabili all interno delle
 * double quotes, posso rendere tutte i vari token dei WORD_TOKEN generici
 * per il momento.
*/

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
/* 
int syntax_error_handler(t_token *head)
{
    t_token *ptr;

    ptr = head;
    if (check_for_non_valid_char_list(ptr, "{}();\\&*") == 1)
    {
       printf("Invalid character found!\n");
       return (ERROR);
    }
    change_non_special_tokens_to_word_tokens(head);
    while(ptr)
    {
        if (ptr->type == PIPE_TOKEN)
        {
            if (handle_pipe_synt_error_tokens(ptr) == 0)
            {
                printf("Syntax error near unexpected token '|'\n");
                return (ERROR);
            }
        }
         else if (ptr->type == GREATER_TOKEN)
        {
            if (handle_greater_synt_error_tokens(ptr) == 0)
            {
                printf("Syntax error near unexpected token '>'\n");
                return (ERROR);
            }    
        }
        else if (ptr->type == LESSER_TOKEN)
        {
            if (handle_lesser_synt_error_tokens(ptr) == 0)
            {
                printf("Syntax error near unexpected token '<'\n");
                return (ERROR);
            }   
        }    
        ptr = ptr->next;
    }
    return (SUCCESS);
} */


/**Ugly lo so, ma mi serve per rimuovere i whitespace dalla
 * lista di token 
*/

void remove_whitespaces(t_token *head)
{
    t_token *ptr;
    t_token *tmp;

    tmp = NULL;
    ptr = head;
    while(ptr)
    {
        if(ptr->type == WHITESPACE_TOKEN)
        {
            if(!ptr->prev && ptr->next)
            {
                tmp = ptr->next;
                free(ptr->value);
                free(ptr);
                ptr = tmp;
            }
            else if (!ptr->next && ptr->prev)
            {
                tmp = ptr->prev;
                free(ptr->value);
                free(ptr);
                ptr = tmp;
            }
            else if(ptr->prev && ptr->next)
            {
                tmp = ptr->next;
                ptr->prev->next = ptr->next;
                ptr->next->prev = ptr->prev;
                free(ptr->value);
                free(ptr);
                ptr = tmp;
            }
            else
            {
                free(ptr->value);
                free(ptr);
            }
        }
        ptr = ptr->next;
    }
}

int syntax_error_handler(t_token *head)
{
    t_token *ptr;

    ptr = head;
    if (check_for_non_valid_char_list(ptr, "{}();\\&*") == 1)
    {
       printf("Invalid character found!\n");
       return (ERROR);
    }
    change_non_special_tokens_to_word_tokens(head);
    remove_whitespaces(head);
    ptr = head;
    while(ptr)
    {
        if (ptr->type == PIPE_TOKEN)
        {
            if (handle_pipe_synt_error_tokens(ptr) == 0)
            {
                printf("Syntax error near unexpected token '|'\n");
                return (ERROR);
            }
        }
         else if (ptr->type == GREATER_TOKEN)
        {
            if (handle_greater_synt_error_tokens(ptr) == 0)
            {
                printf("Syntax error near unexpected token '>'\n");
                return (ERROR);
            }    
        }
        else if (ptr->type == LESSER_TOKEN)
        {
            if (handle_lesser_synt_error_tokens(ptr) == 0)
            {
                printf("Syntax error near unexpected token '<'\n");
                return (ERROR);
            }   
        }
        /**questi devo scrivere*/
        else if (ptr->type == HEREDOC_TOKEN)
        {
            if(headle_heredoc_syntax_error_tokens(ptr) == 0)
            {
                printf("Syntax error near unexpected token '<<'\n");
                return (ERROR);
            }
        } 
        else if (ptr->type == REDIR_OUT_TOKEN)
        {
            if(handle_redir_out_syntax_error_tokens(ptr) == 0)
            {
                printf("Syntax error near unexpected token '>&'\n");
                return (ERROR);
            }
        } 
        ptr = ptr->next;
    }
    return (SUCCESS);
}
