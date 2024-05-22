/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rileone <rileone@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 17:02:26 by rileone           #+#    #+#             */
/*   Updated: 2024/05/22 14:42:38 by rileone          ###   ########.fr       */
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
    if (token->type != DOUBLE_QUOTES_TOKEN && token->type != WHITESPACE_TOKEN)
        token->value = ft_strtrim(tmp_not_trimmed, " ");
    else
        token->value = ft_strdup(tmp_not_trimmed);
    free(tmp_not_trimmed);
}

t_token *token_new(char *data)
{
    t_token *token = malloc(sizeof(t_token));
    if (token)
    {
        token->value = NULL;
        token->type = 0;
        token->next = NULL;
        token->prev = NULL;
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
    new_token->prev = current;
}

void token_print(t_token *head)
{
    t_token *ptr;

    ptr = head;
    while(ptr)
    {
        ft_printf("%s", ptr->value);
        ptr = ptr->next;
    }
    ft_printf("\n");
}

void redirection_clear(t_token **head)
{
    t_token *temp;
    
    temp = *head;
    free(temp->value);
    temp->next = NULL;
    temp->prev = NULL;
    free(temp);
    
}