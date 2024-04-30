/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rileone <rileone@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 17:02:26 by rileone           #+#    #+#             */
/*   Updated: 2024/04/29 18:25:28 by rileone          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "../../includes/lexer.h"

void set_token_values(t_token *token, t_token_info *info) 
{
    int len;
    char *tmp_not_trimmed;

    len = info->end - info->start;
    token->type = info->type;

    tmp_not_trimmed = ft_substr(info->string, info->start, len);
    token->value = ft_strtrim(tmp_not_trimmed, " ");
}

t_token *token_new(char *data)
{
    t_token *token = malloc(sizeof(t_token));
    if (token)
    {
        token->value = NULL;
        token->type = 0;
        token->next = NULL;
    }
    (void)data;
    return token;
}

void token_add_back(t_token **head, t_token *new_token)
{
    t_token *current;
    if (!head || !new_token)
        return;
    
    if (!*head)
    {
        *head = new_token;
        return;
    }
    current = *head;
    while (current->next)
        current = current->next;
    
    current->next = new_token;
}

int token_size(t_token *head)
{
    int size;


    t_token *current;

    current = head;
    size = 0;
    while (current)
    {
        size++;
        current = current->next;
    }
    
    return size;
}
void token_clear(t_token **head)
{
    t_token *current = *head;
    t_token *temp;
    
    while (current)
    {
        temp = current;
        current = current->next;
        free(temp);
    }
    
    *head = NULL;
}