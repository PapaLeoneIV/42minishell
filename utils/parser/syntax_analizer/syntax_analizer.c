/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_analizer.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rileone <rileone@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 11:26:41 by fgori             #+#    #+#             */
/*   Updated: 2024/06/28 16:39:36 by rileone          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

/**Una volta aver tokenizzato ed espanso le variabili all interno delle
 * double quotes, posso rendere tutte i vari token dei WORD_TOKEN generici
 * per il momento.
*/
int	check_for_non_valid_char_list(t_token *ptr, char *non_valid_char)
{
	int	i;

	while (ptr)
	{
		i = 0;
		if (ptr->type == DOUBLE_QUOTES_TOKEN || ptr->type == SING_QUOTES_TOKEN
			|| ptr->type == HERDOC_FILENAME_WITHQUOTES)
		{
			ptr = ptr->next;
			continue ;
		}
		while (ptr->value[i] != '\0')
		{
			if (ft_strchr(non_valid_char, ptr->value[i]))
				return (SUCCESS);
			i++;
		}
		ptr = ptr->next;
	}
	return (ERROR);
}

void	change_non_special_tokens_to_word_tokens(t_token *head)
{
	t_token	*ptr;

	ptr = head;
	while (ptr)
	{
		if (ptr->type == DOLLAR_TOKEN || ptr->type == SING_QUOTES_TOKEN
			|| ptr->type == DOUBLE_QUOTES_TOKEN)
			ptr->type = WORD_TOKEN;
		ptr = ptr->next;
	}
}

/**Ugly lo so, ma mi serve per rimuovere i whitespace dalla
 * lista di token*/

void	remove_whitespaces(t_token **head)
{
	t_token	*ptr;
	t_token	*tmp;

	ptr = *head;
	tmp = NULL;
	while (ptr)
	{
		if (ptr->type == WHITESPACE_TOKEN)
		{	
			tmp = ptr->next;
			if(ptr->prev == NULL)
			{
				(*head) = ptr->next;
				ptr->next->prev = NULL;
			}
			else
			{
				if(ptr->next == NULL)
					ptr->prev->next = NULL;
				else
				{
					ptr->next->prev = ptr->prev;
					ptr->prev->next = ptr->next;	
				}
				
			}
			free(ptr->value);
			free(ptr);
			ptr = NULL;
			ptr = tmp;
		}
		else
			ptr = ptr->next;
	}
}

static int refinement_list(t_token *ptr, t_token **head)
{
	if (check_for_non_valid_char_list(ptr, "{}();\\&") == 1)
	{
		write(2, "Invalid character found!\n", 26);
		return (ERROR);
	}
	change_non_special_tokens_to_word_tokens(*head);
	remove_whitespaces(head);
	return (SUCCESS);
}

static int syn_err_core_logic(t_token	*ptr)
{
	while (ptr)
	{
		if (ptr->type == PIPE_TOKEN && !handle_pipe_synt_error_tokens(ptr))
			return (ERROR);
		else if (ptr->type == GREATER_TOKEN
			&& !handle_greater_synt_error_tokens(ptr))	
				return (ERROR);
		else if (ptr->type == LESSER_TOKEN
			&& !handle_lesser_synt_error_tokens(ptr))
			return (ERROR);
		else if (ptr->type == HEREDOC_TOKEN
			&& !headle_heredoc_syntax_error_tokens(ptr))
			return (ERROR);
		else if (ptr->type == REDIR_OUT_TOKEN
			&& !handle_redirout_synt_error_tokens(ptr))
			return (ERROR);
		ptr = ptr->next;
	}
	return (SUCCESS);
}

int	syntax_error_handler(t_token **head)
{
	t_token	*ptr;

	ptr = *head;
	if (refinement_list(ptr, head) == ERROR)
		return (ERROR);
	ptr = *head;
	if(syn_err_core_logic(ptr) == ERROR)
		return (ERROR);	
	return (SUCCESS);
}
