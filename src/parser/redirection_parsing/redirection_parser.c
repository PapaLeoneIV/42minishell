/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_parser.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rileone <rileone@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 22:23:53 by rileone           #+#    #+#             */
/*   Updated: 2024/07/04 10:53:26 by rileone          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

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

int	redirector(t_command **cmd_node, t_token **tmp_list, t_token **node,
		int *check)
{
	if (handle_redirection_logic(*node, *cmd_node) == SUCCESS)
	{
		*check = remove_redir(node);
		if (*check == 2)
			*tmp_list = *node;
	}
	if (*check == -3)
	{
		tmp_list = NULL;
		return (ERROR);
	}
	else if (*check != 2)
		*node = (*node)->next;
	*check = -1;
	return (SUCCESS);
}

void	init_parser_red(t_parser_red *pars)
{
	pars->check = 0;
	pars->check = 0;
	pars->tmp_list = NULL;
	pars->node = NULL;
	pars->ptr = NULL;
	pars->i = 0;
}

void	copy_mtx_and_add_back(t_parser_red *pars, t_shell *shell)
{
	pars->cmd_node->cmd = from_lst_to_mtx(pars->tmp_list);
	free_tokens(pars->tmp_list);
	add_back_commands(shell->cmd_info, pars->cmd_node);
}

int	parse_redirections(t_token *head, t_shell *shell)
{
	t_parser_red	*pars;

	pars = ft_calloc(1, sizeof(t_parser_red));
	init_parser_red(pars);
	pars->ptr = head;
	shell->cmd_info = ft_calloc(1, sizeof(t_command *));
	while (pars->ptr && pars->i++ < count_pipes(head) + 1)
	{
		pars->check = -1;
		pars->cmd_node = new_command(pars->i - 1);
		pars->tmp_list = split_command_based_on_pipes(&pars->ptr);
		pars->node = pars->tmp_list;
		while (pars->node != NULL && pars->node->type != PIPE_TOKEN)
		{
			if (redirector(&pars->cmd_node, &pars->tmp_list,
					&pars->node, &pars->check) == ERROR)
			{
				pars->tmp_list = NULL;
				pars->node = NULL;
			}
		}
		copy_mtx_and_add_back(pars, shell);
	}
	free(pars);
	return (SUCCESS);
}
