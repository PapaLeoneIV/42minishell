

#include "minishell.h"

static int get_char_type_heredoc(char *str, t_parser *pars, int count)
{
    if (str[count] == ' ')
		return (WHITESPACE_CHAR);
	else if (str[count] == '$')
		return (DOLLAR_CHAR);
	else if (str[count] == '?')
		return (QUESTION_MARK_CHAR);
	else if (str[count] == '\n')
		return (NEWLINE_CHAR);
	else if (ft_isalpha(str[count]) || valid_regchar(str, pars))
		return (REG_CHAR);
	else if (ft_isdigit(str[count]))
		return (DIGIT_CHAR);
	return (TERMINATOR_CHAR);
}

static void general_state_handler_heredoc(char *input, t_parser* pars, t_shell *shell)
{
    char next;
	next = -1;
    if (pars->char_type == WHITESPACE_CHAR || pars->char_type == DOLLAR_CHAR || pars->char_type == TERMINATOR_CHAR)
    {
        if (input[pars->count + 1])
			next = get_char_type(input, pars, pars->count + 1);
		if (pars->char_type == DOLLAR_CHAR && next == WHITESPACE_CHAR)
		{
			slice_token_string_doll_spec_case(input, pars);
			return ;
		}
        if (pars->count > pars->start)
			slice_token_string(input, pars);
        if(pars->char_type == WHITESPACE_CHAR)
            slice_single_char_token(input, pars, shell);
    	if (pars->char_type == SQUOTES_CHAR || pars->char_type == DQUOTES_CHAR  || pars->char_type == DOLLAR_CHAR) 
			check_and_change_status(&pars->state, pars->char_type, pars);
    }
}

static int slice_end_token_heredoc(char *stringa, t_parser *pars, t_shell *shell)
{
	if (stringa[pars->count] == '\0')
		return 0;
	else if (pars->state == STATE_DOLLAR)
		pars->info = (t_token_info){DOLLAR_TOKEN, stringa, pars->start, pars->count + 1};
	else 
		pars->info = (t_token_info){WORD_TOKEN, stringa, pars->start, pars->count + 1};
	pars->token = token_new(NULL);
	set_token_values(pars->token, &pars->info);
	if (pars->token->type == WORD_TOKEN && !ft_strncmp(pars->token->value, "", ft_strlen(pars->token->value)))
	{
	 	free(pars->token->value);
		free(pars->token); 
		return SUCCESS;
	}
	if (pars->token->type == DOLLAR_TOKEN && ft_strncmp(pars->token->value, "$", ft_strlen(pars->token->value)))
	{
		expand_env_var(&pars->token->value, shell);
		if(pars->token->value)
			token_add_back(&pars->head, pars->token);
		else
		{
			free(pars->token->value);
			free(pars->token);
		}
	}
	else
		token_add_back(&pars->head, pars->token);
	return (SUCCESS);
}
char *join_token_values(t_token *list)
{
    char *output;   
    char *new_output; 
    t_token *ptr;

    output = NULL;
    ptr = list;
    while (ptr != NULL)
    {
        new_output = ft_strjoin(output, ptr->value);
        free(output);
        output = new_output;
        ptr = ptr->next;
    }

    return output;
}

char *heredoc_tokenizer(char *input, t_shell *shell)
{
    t_parser pars;
    char *output;
    pars = (t_parser){0};
    while(input[pars.count])
    {  
        pars.char_type = get_char_type_heredoc(input, &pars, pars.count);
        if(pars.state == STATE_GENERAL)
            general_state_handler_heredoc(input, &pars, shell);
        else if (pars.state == STATE_DOLLAR && ((pars.char_type != REG_CHAR && pars.char_type != DIGIT_CHAR)
		|| (pars.char_type == DIGIT_CHAR && input[pars.count - 1] == '$')))
			dollar_state_handler(input, &pars, shell);				
        if (input[pars.count + 1] == '\0' && !slice_end_token_heredoc(input, &pars, shell))
		{
				free_tokens(pars.head);
				return (NULL);																			//SLICE END TOKEN						
		}
        pars.count++;
    }
    output = join_token_values(pars.head);
    free_tokens(pars.head);
    return output;
}
