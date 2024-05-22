

#include "../../../includes/lexer.h"

int look_next_token_pipe(t_token *next)
{
    if (next->next == NULL)
        return (ERROR);
    if (next->next->type != WORD_TOKEN && next->next->type != GREATER_TOKEN
    && next->next->type != LESSER_TOKEN && next->next->type != REDIR_OUT_TOKEN)
        return (ERROR);
    return (SUCCESS);
}

int handle_pipe_synt_error_tokens(t_token *ptr)
{
    if(ptr->next == NULL || ptr->prev == NULL)
        return (ERROR);
    if (ptr->prev->type == WHITESPACE_TOKEN)
    {
        if (ptr->prev->prev == NULL)
            return (ERROR);
        if (ptr->prev->prev->type != WORD_TOKEN)
            return (ERROR);
    }
    if ((ptr->next->type == WHITESPACE_TOKEN && look_next_token_pipe(ptr->next))
    || ptr->next->type == WORD_TOKEN)
        return (SUCCESS);
    return (ERROR);
}

/**Se all interno della stringa che ci viene passata e' presente uno dei caratteri
 * all interno della variabile non_valid_char posso ritornare un errore
*/

int check_for_non_valid_char_list(t_token *ptr, char *non_valid_char)
{
    int i;

    while(ptr)
    {
        i = 0;
        if (ptr->type == DOUBLE_QUOTES_TOKEN || ptr->type == SING_QUOTES_TOKEN)
        {
            ptr = ptr->next;
            continue;   
        }
        while(ptr->value[i] != '\0')
        {
            if(ft_strchr(non_valid_char, ptr->value[i]))
                return (SUCCESS);
            i++;
        }
        ptr = ptr->next;
    }
    return (ERROR);
}

int handle_greater_synt_error_tokens(t_token *ptr)
{
    t_token *tmp;

    tmp = ptr;
    if (tmp->next == NULL)
        return (ERROR);
/*     if (tmp->prev->type == WHITESPACE_TOKEN)
    {
        if (tmp->prev->prev == NULL)
            return (ERROR);
        if (tmp->prev->prev->type == WORD_TOKEN && !ft_isnumber(tmp->prev->value))
            return (SUCCESS);
    } */
    else if(tmp->prev->type == WORD_TOKEN && ft_isnumber(tmp->prev->value))
        return (ERROR);
    if (tmp->next->type == WHITESPACE_TOKEN)
    {
        if (tmp->next->next == NULL)
            return (ERROR);
        if (tmp->next->next->type == WORD_TOKEN)
            return (SUCCESS);
    }
    else if (tmp->next->type == WORD_TOKEN)
        return (SUCCESS);    
    return (ERROR); 
}

int handle_lesser_synt_error_tokens(t_token *ptr)
{
    t_token *tmp;

    tmp = ptr;
    if (tmp->next == NULL)
        return (ERROR);
    if (tmp->next->type == WHITESPACE_TOKEN)
    {
        if (tmp->next->next == NULL)
            return (ERROR);
        if (tmp->next->next->type == WORD_TOKEN)
            return (SUCCESS);
    }
    else if (tmp->next->type == WORD_TOKEN)
        return (SUCCESS);    
    return (ERROR); 
}
