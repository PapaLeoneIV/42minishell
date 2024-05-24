

#include "../../../includes/lexer.h"



int handle_pipe_synt_error_tokens(t_token *ptr)
{
    if(ptr->next == NULL || ptr->prev == NULL)
        return (ERROR);
    if(ptr->next->type != WORD_TOKEN && ptr->next->type != HERDOC_FILENAME_WITHQUOTES
    && ptr->next->type != GREATER_TOKEN && ptr->next->type != LESSER_TOKEN
    && ptr->next->type != REDIR_OUT_TOKEN && ptr->next->type != HEREDOC_TOKEN)
        return (ERROR);
    return (SUCCESS);
}

/**Se all interno della stringa che ci viene passata e' presente uno dei caratteri
 * all interno della variabile non_valid_char posso ritornare un errore
*/

int headle_heredoc_syntax_error_tokens(t_token *ptr)
{
    if(ptr->next && (ptr->next->type == WORD_TOKEN || ptr->next->type == HERDOC_FILENAME_WITHQUOTES))
        return (SUCCESS);
    return (ERROR);
}
int handle_redirout_synt_error_tokens(t_token *ptr)
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
