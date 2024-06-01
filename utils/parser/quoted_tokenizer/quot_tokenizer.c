
#include "../../includes/lexer.h"

int valid_regchar_quoted(char c)
{
	char *valid_char;
	int len;
	int i;

	i = 0;
	valid_char = "_";
	len = ft_strlen(valid_char);
	while(i < len)
	{
		if(ft_charchar(c, valid_char[i]))
			return (1);
		i++;
	}
	return (0);
}
int get_char_type_quoted(char c)
{
	if (c == ' ')
		return (WHITESPACE_CHAR);
	else if (c == '$')
		return (DOLLAR_CHAR);
	else if (c == '?')
		return (QUESTION_MARK_CHAR);
	else if (ft_isalpha(c) || valid_regchar_quoted(c))
		return (REG_CHAR);
	else if (ft_isdigit(c))
		return (DIGIT_CHAR);
	return (DOLLAR_SPECIAL_CHAR);
}

t_parser *tokenize_quoted_values(t_token *node, t_shell *shell)
{	
	t_parser *parser;

	if (node && node->value && node->value[0] == '\0')
		return (NULL);
	parser = ft_calloc(1, sizeof(t_parser));
	parser->state = STATE_GENERAL;
	parser->start = 0;
	parser->count = 0;
	parser->head = NULL;
	while(node->value[parser->count])
	{
		parser->char_type = get_char_type_quoted(node->value[parser->count]);
		if (parser->state == STATE_GENERAL)
			general_state_handler_quoted(node->value, parser, shell);
		else if (parser->state == STATE_DOLLAR && ((parser->char_type != REG_CHAR && parser->char_type != DIGIT_CHAR)
		|| (parser->char_type == DIGIT_CHAR && node->value[parser->count - 1] == '$')))
			dollar_state_handler_quoted(node->value, parser, shell);												//DOLLAR STATE
		if (node->value[parser->count + 1] == '\0')
		{
			if (!slice_end_token(node->value, parser, shell))
				return (0);																			//SLICE END TOKEN						
		}
		parser->count++;
	}
	return parser;
}

void general_state_handler_quoted(char *stringa, t_parser *pars, t_shell *shell)
{
	if (pars->char_type == WHITESPACE_CHAR || pars->char_type == DOLLAR_CHAR)
	{
		if (pars->count > pars->start)  																									//se ho incontrato uno dei carattere nell if precedente posso tagliare la stringa
			slice_token_string(stringa, pars);
		if (pars->char_type == WHITESPACE_CHAR)
			slice_single_char_token(stringa, pars, shell);
		if (pars->char_type == DOLLAR_CHAR)  						//cambio lo state machine per gestire le virgolette
			check_and_change_status(&pars->state, pars->char_type, pars);
	}
}
void dollar_state_handler_quoted(char *stringa, t_parser *pars, t_shell *shell)
{
	/***qui dipende se voglio gestire $1 $2 $3 $? ....*/


	/***per il momento $? viene espanso e risulta uguale a NULL (ERRORE)*/
	if ((pars->count > pars->start && pars->char_type == DIGIT_CHAR && stringa[pars->count - 1] == '$') ||
	(pars->count > pars->start && pars->char_type == QUESTION_MARK_CHAR && stringa[pars->count - 1] == '$'))
	{
		pars->token = token_new(NULL);
		pars->info = (t_token_info){DOLLAR_TOKEN, stringa, pars->start, pars->count + 1};
		set_token_values(pars->token, &pars->info);
		if (strcmp(pars->token->value, "$0") == 0)
			pars->token->value = ft_strdup("bash");
		else
			pars->token->value = NULL;
		token_add_back(&pars->head, pars->token);
		pars->start = pars->count + 1;
	}
	if (pars->count > pars->start)
	{
		pars->token = token_new(NULL);
		pars->info = (t_token_info){DOLLAR_TOKEN, stringa, pars->start, pars->count}; 
		set_token_values(pars->token, &pars->info);
		if (pars->token->value)
		{
			token_add_back(&pars->head, pars->token);
			expand_env_var(&pars->token->value, shell);		
		}
		else
			free(pars->token);
		pars->start = pars->count;
		pars->count--;
	}
	
	pars->state = STATE_GENERAL;
}