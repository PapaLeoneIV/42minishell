/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_parser.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rileone <rileone@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 22:23:53 by rileone           #+#    #+#             */
/*   Updated: 2024/06/21 11:36:17 by rileone          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/lexer.h"



t_token	*look_tokens_ahead(t_token *current)
{
	if (current->next == NULL)
		return (NULL);
	if (current->next->type != WORD_TOKEN
		&& current->next->type != HERDOC_FILENAME_WITHQUOTES)
		return (NULL);
	if (current->next->type == WORD_TOKEN)
		return (current->next);
	if (current->next && (current->next->type == WORD_TOKEN
			|| current->next->type == HERDOC_FILENAME_WITHQUOTES))
		return (current->next);
	return (NULL);
}

int	count_pipes(t_token *head)
{
	t_token	*ptr;
	int		counter;

	counter = 0;
	ptr = head;
	while (ptr)
	{
		if (ptr->type == PIPE_TOKEN)
			counter++;
		ptr = ptr->next;		
	}
	return (counter);
}

/**La lista di token viene splittata in base alle pipeline per un
 * piu facile parsing delle redirection
*/

t_token	*split_command_based_on_pipes(t_token **ptr)
{
	t_token	*newlist;
	t_token	*newnode;

	newlist = NULL;
	while (*ptr && (*ptr)->type != PIPE_TOKEN)
	{
		newnode = token_new(NULL);
		newnode->value = ft_strdup((*ptr)->value);
		newnode->type = (*ptr)->type;
		if (!newnode)
		{
			free_tokens(newlist);
			return (NULL);
		}
		token_add_back(&newlist, newnode);
		(*ptr) = (*ptr)->next;
	}
	if ((*ptr) && (*ptr)->type == PIPE_TOKEN)
		(*ptr) = (*ptr)->next;
	return (newlist);
}



int	handle_redirection_logic(t_token *node, t_command *cmd_node)
{
	t_token	*node_ahead;
	t_redir	*tmp;

	if (node->type == GREATER_TOKEN || node->type == REDIR_OUT_TOKEN
		|| node->type == LESSER_TOKEN || node->type == HEREDOC_TOKEN)
	{
		node_ahead = look_tokens_ahead(node);
		if (node_ahead == NULL)
			return (ERROR);
		if (node_ahead->type == WORD_TOKEN || (node->type == HEREDOC_TOKEN
				&& node_ahead->type == HERDOC_FILENAME_WITHQUOTES))
		{
			if (!cmd_node->redirection_info)
				cmd_node->redirection_info = ft_calloc(1, sizeof(t_redir *));
			if (node_ahead->type == HERDOC_FILENAME_WITHQUOTES)
				tmp = new_redir_node(node->type, node_ahead->value, 0);
			else
				tmp = new_redir_node(node->type, node_ahead->value, 1);
			add_back_redirections(cmd_node->redirection_info, tmp);
			return (SUCCESS);
		}
	}
	return (ERROR);
}


int	remove_redir(t_token **redir)
{
	int		i;
	t_token	*tmp;

	i =0;
	tmp = (*redir);
	if ((*redir)->prev && (*redir)->next->next)
	{
		(*redir) = (*redir)->prev;
		(*redir)->next = (*redir)->next->next->next;
		(*redir)->next->prev = (*redir);
		i++;
	}
	else if (!(*redir)->prev && (*redir)->next->next)
	{
		(*redir) = (*redir)->next->next;
		(*redir)->prev = NULL;
		i += 2;
	}
	else if ((*redir)->prev && !(*redir)->next->next)
	{
		(*redir)->prev->next = NULL;	
		*redir = (*redir)->prev;
	}
	return (redirection_clear(&tmp->next), redirection_clear(&tmp), i);
}


void	redirector(t_command **cmd_node, t_token **tmp_list,
	t_token **node, int *check)
{
	if (handle_redirection_logic(*node, *cmd_node) == SUCCESS)
	{
		*check = remove_redir(node);
		if (*check == 2)
			*tmp_list = *node;
	}
	if (*check != 2)
		*node = (*node)->next;
	*check = -1;
}


int	parse_redirections(t_token *head, t_shell *shell)
{
	t_command	*cmd_node;
	t_token		*tmp_list;
	t_token		*node;
	t_token		*ptr;
	int			check;
	int			i;

	ptr = head;
	shell->cmd_info = ft_calloc(1, sizeof(t_command *));
	i = 0;
	while (ptr && i < count_pipes(head) + 1)
	{
		check = -1;
		cmd_node = new_command(i);
		tmp_list = split_command_based_on_pipes(&ptr);
		node = tmp_list;
		while (node != NULL && node->type != PIPE_TOKEN)
			redirector(&cmd_node, &tmp_list, &node, &check);
		cmd_node->cmd = from_lst_to_mtx(tmp_list);
		free_tokens(tmp_list);
		add_back_commands(shell->cmd_info, cmd_node);
		i++;
	}
	return (SUCCESS);
}