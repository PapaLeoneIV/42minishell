/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_extra_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgori <fgori@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 11:25:48 by fgori             #+#    #+#             */
/*   Updated: 2024/07/02 11:29:33 by fgori            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

static int	refinement_list(t_token *ptr, t_token **head)
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

static int	syn_err_core_logic(t_token	*ptr)
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
	if (syn_err_core_logic(ptr) == ERROR)
		return (ERROR);
	return (SUCCESS);
}
