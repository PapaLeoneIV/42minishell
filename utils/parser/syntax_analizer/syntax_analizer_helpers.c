

#include "../../../includes/lexer.h"



int handle_pipe_synt_error_tokens(t_token *ptr)
{
    if(ptr->next == NULL || ptr->prev == NULL)
        return (ERROR);
    if (ptr->prev->type != WORD_TOKEN && ptr->prev->type != HERDOC_FILENAME_WITHQUOTES)
            return (ERROR);
    if(ptr->next->type == WORD_TOKEN || ptr->prev->type == HERDOC_FILENAME_WITHQUOTES)
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
        if (ptr->type == DOUBLE_QUOTES_TOKEN || ptr->type == SING_QUOTES_TOKEN 
        || ptr->type == HERDOC_FILENAME_WITHQUOTES)
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
    else if(tmp->prev && tmp->prev->type == WORD_TOKEN && ft_isnumber(tmp->prev->value))
        return (ERROR);
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
    else if (tmp->next->type == WORD_TOKEN)
        return (SUCCESS);
    return (ERROR);
}
