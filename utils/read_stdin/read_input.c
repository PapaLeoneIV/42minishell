/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_input.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rileone <rileone@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/21 17:12:07 by rileone           #+#    #+#             */
/*   Updated: 2024/05/22 16:14:04 by rileone          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "../../includes/lexer.h"


/**se incontro una redirection controllo che il token successivo sia necessariamente una parola*/


t_token *look_tokens_ahead(t_token *current)
{
	if (current->next == NULL)
		return (NULL);
	if (current->next->type != WORD_TOKEN && current->next->type != WHITESPACE_TOKEN)
		return (NULL);
	if (current->next->type == WORD_TOKEN)
		return current->next;
	if(current->next->type == WHITESPACE_TOKEN && (current->next->next && current->next->next->type == WORD_TOKEN))
		return current->next->next;
	
	return NULL;
	
}

int check_if_is_a_redirection(t_token *node)
{
	/**bisogna aggiungerci la gestione dell heredoc*/
	if(node->type == GREATER_TOKEN || node->type == REDIR_OUT_TOKEN || node->type == LESSER_TOKEN)
		return (SUCCESS);
	return (0);
}

/**Self explanatory*/

int count_pipes(t_token *head)
{
	t_token *ptr;
	int counter;

	counter = 0;
	ptr = head;
	while(ptr)
	{
		if(ptr->type == PIPE_TOKEN)
			counter++;
		ptr = ptr->next;		
	}
	return counter;
}

/**Copio le informazioni alll interno del nuovo token */

void copy_token_info(t_token **new, t_token *old)
{
	t_token *tmp;

	tmp = *new;

	tmp->value = ft_strdup(old->value);
	tmp->type = old->type;
}

/**La lista di token viene splittata in base alle pipeline per un
 * piu facile parsing delle redirection
*/

t_token *split_command_based_on_pipes(t_token **ptr)
{
	t_token *newlist;
	t_token *newnode;
	
	newlist = NULL;
	while(*ptr && (*ptr)->type != PIPE_TOKEN)
	{
		newnode = token_new(NULL);
		copy_token_info(&newnode, *ptr);
		if(!newnode)
		{
			free_tokens(newlist); 
			return NULL;
		}				
		token_add_back(&newlist, newnode);
		(*ptr) = (*ptr)->next;
	}
	if ((*ptr) && (*ptr)->type == PIPE_TOKEN)
		(*ptr) = (*ptr)->next;
	return newlist;
}

t_redir *new_redir_node(int type, char *value)
{
	t_redir *redir_node;

	redir_node = ft_calloc(1, sizeof(t_redir));
	redir_node->filename = ft_strdup(value);
	redir_node->type_of_redirection = type;
	redir_node->next = NULL;
	return redir_node;
}

void add_back_redirections(t_redir **lst, t_redir *node)
{
	t_redir	*ptrlst;

	if (*lst == NULL)
	{
		*lst = node;
		return ;
	}
	ptrlst = *lst;
	while (ptrlst->next != NULL)
		ptrlst = ptrlst->next;
	ptrlst->next = node;
}


int handle_redirection_logic(t_token *node, t_shell *shell, t_command *cmd_node)
{

	t_token *node_ahead;
	t_redir *redirection_node;
	(void)shell;
	
	if(check_if_is_a_redirection(node))
	{
		node_ahead = look_tokens_ahead(node);
		if (node_ahead == NULL)
			return (ERROR);
		if (node_ahead->type == WORD_TOKEN)
		{	
			redirection_node = new_redir_node(node->type, node_ahead->value);
			add_back_redirections(cmd_node->redirection_info, redirection_node);
			return SUCCESS;
		}
	}
	return ERROR;
}


t_command *new_command(int counter)
{
		t_command *cmd_node;

		cmd_node = ft_calloc(1, sizeof(t_command));
		cmd_node->cmd = NULL;
		cmd_node->cmd_id = counter;
		cmd_node->redirection_info = ft_calloc(1, sizeof(t_redir*));
		cmd_node->next = NULL;

		return cmd_node;
}

void add_back_commands(t_command **lst, t_command *node)
{
	t_command	*ptrlst;

	if (*lst == NULL)
	{
		*lst = node;
		return ;
	}
	ptrlst = *lst;
	while (ptrlst->next != NULL)
		ptrlst = ptrlst->next;
	ptrlst->next = node;
}

int remove_redir(t_token **redir)
{
	int		i;
	t_token *tmp;

	i = 0;
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
		

	redirection_clear(&tmp->next);
	redirection_clear(&tmp);
	return (i);
}

char **from_lst_to_mtx(t_token *head)
{
	int i;
	int len;
	char **mtx;
	t_token *ptr;

	ptr = head;
	i = 0;
	len = 0;
	while(ptr)
	{
		ptr = ptr->next;
		len++;
	}
	ptr = head;	
	mtx = ft_calloc(len + 1, sizeof(char *));
	while(i < len)
	{
		mtx[i] = ft_strdup(ptr->value);
		i++;
		ptr = ptr->next;
	}
	return mtx;
}

int parse_redirections(t_token *head, t_shell *shell)
{
	t_command *cmd_node;
	t_token *tmp_list;
	t_token *node;
	t_token *ptr;
	int		check;
	int n_pipes;
	int i;
	(void)shell;
	
	ptr = head;
	n_pipes = count_pipes(head) + 1;

	shell->cmd_info = ft_calloc(1, sizeof(t_command*));
	
	i = 0;
	while(ptr && i < n_pipes)
	{
		check = -1;
		cmd_node = new_command(i);
		tmp_list = split_command_based_on_pipes(&ptr);  
		node = tmp_list;
		while (node != NULL && node->type != PIPE_TOKEN)
		{
			if (handle_redirection_logic(node, shell, cmd_node) == SUCCESS)
			{
				check = remove_redir(&node);
				if (check == 2)
					tmp_list = node;
			}
			if (check != 2)
				node = node->next;
			check = -1;
		}
		cmd_node->cmd = from_lst_to_mtx(tmp_list);
		int j;
		j = 0;
		while(cmd_node->cmd && cmd_node->cmd[j])
		{
			printf("%s\n", cmd_node->cmd[j]);
			j++;
		}
		printf("\n");
		add_back_commands(shell->cmd_info, cmd_node);
		
		/* token_print(tmp_list); */
/*  		free_tokens(tmp_list); */
		i++;
	}
	return (SUCCESS);
}


/**Loop principale dove ricevo la stringa e faccio il parsing*/

void read_from_stdin(t_shell *shell)
{
	t_token     *head;
	char		*input;
 	(void)shell;
	while (true)
	{
		input = readline("(MINISHELL)$");
		head = tokenize_input(input, shell);
  		if (head == NULL)
			continue; 
	 	if (syntax_error_handler(head) == ERROR)
		{
			free_tokens(head);
			continue;
		} 
		/*forse in futuro sara' necessario farsi una copia della lst di token*/
     	if(parse_redirections(head, shell) == ERROR)
			printf("Redirection error\n");
		free(input);
		free_tokens(head);
	}
}

