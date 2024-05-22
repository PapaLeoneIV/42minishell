#include "minishell.h"

void    clean_env_node(t_env **lst)
{
    if ((*lst)->body)
        free((*lst)->body);
    if ((*lst)->head)
        free((*lst)->head);
    free(*lst);
}

void    clean_env_lst(t_env **lst)
{
    t_env   *tmp;

    while ((*lst))
    {
        tmp = (*lst)-> next;
        clean_env_node(lst);
        *lst = tmp;
    }
    free(lst);
}
