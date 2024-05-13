/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_analizer.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rileone <rileone@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/11 10:36:07 by rileone           #+#    #+#             */
/*   Updated: 2024/05/13 16:50:11 by rileone          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/lexer.h"

/* int handle_pipe_synt_error(t_token *ptr)
{
    if (ptr->next == NULL)
        return (0);
    if (ptr->next->type == PIPE_TOKEN)
        return (0);
    return (1);
}

int handle_greater_lesser_synt_error(t_token *ptr)
{
    if (ptr->next == NULL)
        return (0);
    if (ptr->next->type != WORD_TOKEN && ptr->next->type != WHITESPACE_TOKEN)
        return (0);
    return (1);
}
 */
/* int is_num_of_quotes_even(t_token *head, char *input)
{
    int     count_single_quotes;
    int i;
    t_token *ptr;
    i = 0;
    while(input[i] != '\0')
    {
        
        i++;
    }
    
} */

/* int syntax_error_handler(t_token *head, char *input)
{
    t_token *ptr;
    ptr = head;

    (void)input;
  if (is_num_of_quotes_even(head, input) == 0)
        return (0);
    while(ptr)
    {
        if (ptr->type == PIPE_TOKEN)
        {
            if (handle_pipe_synt_error(ptr) == 0)
                return (0);
        }
        else if (ptr->type == GREATER_TOKEN)
        {
            if (handle_greater_lesser_synt_error(ptr) == 0)
                return (0);
        }
        else if (ptr->type == LESSER_TOKEN)
        {
            if (handle_greater_lesser_synt_error(ptr) == 0)
                return (0);
        }
        ptr = ptr->next;
    }
    return (1);
}  */

int valid_regchar_synt_an(char *str, int i, char* non_valid_char)
{
	int len;
	int count;

	count = 0;
	len = ft_strlen(non_valid_char);
	while(count < len)
	{
		if(ft_charchar(str[i], non_valid_char[count]))
			return (1);
		count++;
	}
	return (0);
}

int handle_gr_less_synt_error(char *input, int next_char, char *non_valid_char, char sign)
{
    if (valid_regchar_synt_an(input, next_char, non_valid_char) 
    || input[next_char] == '\0')
        return (0);
    if (input[next_char] == sign)
    {
        if (input[next_char + 1] && input[next_char + 1] == sign)
            return (0);
    }
    return (1);
}


int handle_pipe_synt_error(char *input, int next_char, char *non_valid_char)
{
    if (valid_regchar_synt_an(input, next_char, non_valid_char) 
    || input[next_char] == '\0')
        return (0);
    return (1);
}

int check_for_non_valid_char(char *input, char *non_valid_char)
{
    int len;
    int i;

    i =0;
    len = ft_strlen(input);
    while(i < len)
    {
        if(ft_strchr(non_valid_char, input[i]))
            return (1);
        i++;
    }
    return (0);
}

int check_number_of_quotes(char *input)
{
    int count;
    int d_count;
    int s_count;
    
    count = 0;
    d_count = 0;
    s_count = 0;
    while(input && input[count] != '\0')
    {
        if(input[count] == '"')
        {
            d_count++;
            count++;
            while(input && input[count] && (input[count] != '"' || input[count] != '\0'))
                count++;
            if (input[count] == '"')
                d_count++;
        }
        else if (input[count] == '\'')
        {
            s_count++;
            while(input && (input[count] != '\'' || input[count] != '\0'))
                count++;
            if (input[count] == '\'')
                s_count++;
        }
        count++;
    }
    if(s_count % 2 != 0 || d_count % 2 != 0)
        return (0);
    return (1);
}

int syntax_error_handler(t_token *head, char *input)
{
    int i;
    (void)head;
    i = 0;
    if (check_for_non_valid_char(input, "{}();\\&*") == 1)
        return (0);
    if (check_number_of_quotes(input) == 0)
        return (0);
    while(input[i] != '\0')
    {
        if (input[i] == '|')
        {
            if (handle_pipe_synt_error(input, i + 1, "<>|&;(){}") == 0)
                return (0);
        }
        else if (input[i] == '>')
        {
            if (handle_gr_less_synt_error(input, i + 1, "<|&;(){}", '>') == 0)
                return (0);
        }
        else if (input[i] == '<')
        {
            if (handle_gr_less_synt_error(input, i + 1, ">|&;(){}", '<') == 0)
                return (0);
        }        
        i++;
    }
    return (1);
}


