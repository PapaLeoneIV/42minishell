/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_analizer.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rileone <rileone@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/11 10:36:07 by rileone           #+#    #+#             */
/*   Updated: 2024/05/14 19:57:35 by rileone          ###   ########.fr       */
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
/* int is_num_of_quotes_even(t_token *head, char *input_string)
{
    int     count_single_quotes;
    int i;
    t_token *ptr;
    i = 0;
    while(input_string[i] != '\0')
    {
        
        i++;
    }
    
} */

/* int syntax_error_handler(t_token *head, char *input_string)
{
    t_token *ptr;
    ptr = head;

    (void)input_string;
  if (is_num_of_quotes_even(head, input_string) == 0)
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

int handle_gr_less_synt_error(char *input_string, int next_char, char *non_valid_char, char sign)
{
    if (valid_regchar_synt_an(input_string, next_char, non_valid_char) 
    || input_string[next_char] == '\0')
        return (0);
    if (input_string[next_char] == sign)
    {
        if (input_string[next_char + 1] && input_string[next_char + 1] == sign)
            return (0);
    }
    return (1);
}


int handle_pipe_synt_error(char *input_string, int next_char, char *non_valid_char)
{
    if (valid_regchar_synt_an(input_string, next_char, non_valid_char) 
    || input_string[next_char] == '\0')
        return (0);
    return (1);
}

int check_for_non_valid_char(char *input_string, char *non_valid_char)
{
    int len;
    int i;

    i =0;
    len = ft_strlen(input_string);
    while(i < len)
    {
        if(ft_strchr(non_valid_char, input_string[i]))
            return (1);
        i++;
    }
    return (0);
}

int check_number_of_quotes(char *input_string)
{
    int count;
    int d_count;
    int s_count;
    
    count = 0;
    d_count = 0;
    s_count = 0;
    while(input_string && input_string[count] != '\0')
    {
        if(input_string[count] == '"')
        {
            d_count++;
            count++;
            while(input_string && input_string[count] && (input_string[count] != '"' || input_string[count] != '\0'))
                count++;
            if (input_string[count] == '"')
                d_count++;
        }
        else if (input_string[count] == '\'')
        {
            s_count++;
            while(input_string && (input_string[count] != '\'' || input_string[count] != '\0'))
                count++;
            if (input_string[count] == '\'')
                s_count++;
        }
        count++;
    }
    if(s_count % 2 != 0 || d_count % 2 != 0)
        return (0);
    return (1);
}




/***DEVE ESEERE RISCRITTA USANDO I TOKEN PERCHE DO COME ERRORE (echo ">|"
echo >|
Syntax error)*/
/* int syntax_error_handler(t_token *head, char *input_string)
{
    int i;
    (void)head;
    i = 0;
    if (check_for_non_valid_char(input_string, "{}();\\&*") == 1)
        return (0);
    
    while(input_string[i] != '\0')
    {
        if (input_string[i] == '|')
        {
            if (handle_pipe_synt_error(input_string, i + 1, "<>|&;(){}") == 0)
                return (0);
        }
        else if (input_string[i] == '>')
        {
            if (handle_gr_less_synt_error(input_string, i + 1, "<|&;(){}", '>') == 0)
                return (0);
        }
        else if (input_string[i] == '<')
        {
            if (handle_gr_less_synt_error(input_string, i + 1, ">|&;(){}", '<') == 0)
                return (0);
        }  
        i++;
    }
    return (1);
}

 */

int look_next_token_pipe(t_token *next)
{
    if (next->next == NULL)
        return (0);
    if (next->next->type != WORD_TOKEN && next->next->type != WHITESPACE_TOKEN)
        return (0);
    return (1);
}

int handle_pipe_synt_error_tokens(t_token *ptr)
{
    if(ptr->next == NULL || ptr->prev == NULL)
        return (0);
    if ((ptr->next->type == WHITESPACE_TOKEN && look_next_token_pipe(ptr->next))
    || ptr->next->type == WORD_TOKEN)
        return (1);
    return 0;
}

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
                return (1);
            i++;
        }
        ptr = ptr->next;
    }
    return (0);
}

int handle_gr_less_synt_error_tokens(t_token *ptr)
{
    
}

int syntax_error_handler(t_token *head, char *input_string)
{
    t_token *ptr;

    ptr = head;
    (void)input_string;
    if (check_for_non_valid_char_list(ptr, "{}();\\&*") == 1)
       return 0;
    if (check_number_of_quotes(input_string) == 0)
        return (0);
    while(ptr)
    {
        if (ptr->type == PIPE_TOKEN)
        {
            if (handle_pipe_synt_error_tokens(ptr) == 0)
                return (0);
        }
        else if (ptr->type == GREATER_TOKEN)
        {
            if (handle_gr_less_synt_error_tokens(ptr) == 0)
                return (0);
        }
       /* else if (ptr->type == LESSER_TOKEN)
        {
            
        }
        */    
        ptr = ptr->next;
    }




    return 1;
}

