
#include "../../includes/lexer.h"

t_token *check_prev(t_token *token)
{
	t_token *prev;

	prev = token->prev;
	if (prev == NULL || prev->type == WHITESPACE_TOKEN)
		return NULL;
	if (prev->type == WORD_TOKEN || prev->type == DOUBLE_QUOTES_TOKEN
	|| prev->type == SING_QUOTES_TOKEN || prev->type == DOLLAR_TOKEN)
		return prev; 
	return NULL;
}

void join_tokens(t_token **node, t_token **prev)
{
	(*prev)->value = ft_strjoin((*prev)->value, (*node)->value);
	if((*node)->next)
		(*node)->next->prev = (*prev);
	else
		(*prev)->next = NULL;
	(*prev)->next = (*node)->next;
	free((*node)->value);
	free(*node);
	*node = NULL;
	*node = *prev;
}

void join_tokens_values_when_no_space_between(t_parser *pars, t_shell *shell)
{

	t_token *prev;
	t_token *ptr;
	(void)shell;
	ptr = pars->head;
	while(ptr != NULL)
	{
		prev = check_prev(ptr);
		if (!prev)
		{
			ptr = ptr->next;
			continue;
		}
		if (ptr && (ptr->type == WORD_TOKEN || ptr->type == SING_QUOTES_TOKEN 
		|| ptr->type == DOUBLE_QUOTES_TOKEN || ptr->type == DOLLAR_TOKEN ) && prev)
			join_tokens(&ptr, &prev);
		ptr = ptr->next;
	}
}

char *join_quoted_token_expansion(t_token *head)
{
	char *out;
	
	out = NULL;
	while(head)
	{
		out = ft_strjoin(out, head->value);
		head = head->next; 
	}
	return out;
}

void unpack_quoted_tokens(t_parser *pars, t_shell *shell)
{
	t_token *ptr;
	t_parser *list;

	ptr = pars->head;
	while(ptr != NULL)
	{
		if (ptr->type == DOUBLE_QUOTES_TOKEN)
		{
  			list = tokenize_quoted_values(ptr, shell);
			(void)list;
 			free(ptr->value);
			ptr->value = join_quoted_token_expansion(list->head);
		}
  		ptr = ptr->next;
	}

}