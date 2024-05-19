/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rileone <rileone@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 14:46:54 by rileone           #+#    #+#             */
/*   Updated: 2024/05/19 16:34:47 by rileone          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
#define LEXER_H

#include "./minishell.h"
typedef struct s_shell t_shell;


typedef struct s_token_info
{
	int         type;
	char        *string;
	int         start;
	int         end;
}				t_token_info;

typedef struct s_token
{
	char            *value;
	int             type;  
	struct s_token *next;
	struct s_token *prev;
}				t_token;

typedef struct parser
{
	
	int         state;
	int         char_type;
	int         count;
	int         start;
	t_token     *head;
	t_token     *token;
	t_token_info info;
} 				t_parser;


typedef struct s_commands
{
	char 				**cmd;
	int					in;
	int					out;
	int					type_of_redirection;
	int					first_command;
	char*				filename;
	struct s_commands	*next;
} 			t_command;
enum State
{
	STATE_GENERAL,
	STATE_DQUOTE,
	STATE_SQUOTE,
	STATE_DOLLAR,
};

enum TokenType
{
	WORD_TOKEN,            //0
	PIPE_TOKEN,            //1
	GREATER_TOKEN,         //2
	REDIR_OUT_TOKEN,       //3
	LESSER_TOKEN,          //4
	HEREDOC_TOKEN,         //5
	SING_QUOTES_TOKEN,     //6
	DOUBLE_QUOTES_TOKEN,   //7
	DOLLAR_TOKEN,          //8
	WHITESPACE_TOKEN,      //9

};

enum CharType
{
	WHITESPACE_CHAR,     // 0
	PIPELINE_CHAR,       // 1
	REDIR_INPUT_CHAR,    // 2
	REDIR_OUTPUT_CHAR,   // 3
	REG_CHAR,            // 4
	SQUOTES_CHAR,        // 5
	DQUOTES_CHAR,        // 6
	DOLLAR_CHAR,         // 7
	DOLLAR_SPECIAL_CHAR, // 8
	DIGIT_CHAR,          // 9
	QUESTION_MARK_CHAR,  // 10

};
/*TOKEN CREATION METHODS*/
void		set_token_values(t_token *token, t_token_info *info);
t_token		*token_new(char *data);
void		token_add_back(t_token **head, t_token *new_token);
void		token_print(t_token *head);
void		token_clear(t_token **head);

/*TOKENIZER MAIN FUNCTIONS*/
t_token		*tokenize_input(char *input, t_shell *shell);
int			create_token_list(char *stringa, t_shell *shell, t_parser *pars);


/*TOKENIZER HELPERS*/
int			look_for_another_redirect(char *stringa, t_parser *pars);
int			valid_regchar(char *str, t_parser *pars);
int			get_char_type(char *str, t_parser *pars, int count);

/*TOKENIZER HELPERS(SLICE METHODS)*/
void		slice_single_char_token(char *stringa, t_parser *pars);
void		slice_redirect_token(char *stringa, t_parser *pars);
void		slice_token_string(char *stringa, t_parser *pars);
int			slice_end_token(char *stringa, t_parser *pars, t_shell *shell);
void 		slice_token_string_doll_spec_case(char *stringa, t_parser *pars);

/*TOKENIZER HELPERS(STATE HANDLERS)*/
void		general_state_handler(char *stringa, t_parser *pars);
void		dollar_state_handler(char *stringa, t_parser *pars, t_shell *shell);
void		quoted_state_handler(char *stringa, t_parser *pars);
void		check_and_change_status(int *state, int c, t_parser *pars);

/*QUOTED TOKENIZER HELPERS*/
int			valid_regchar_quoted(char c);
int			get_char_type_quoted(char c);
t_parser	*tokenize_quoted_values(t_token *node, t_shell *shell);
void		general_state_handler_quoted(char *stringa, t_parser *pars);
void		dollar_state_handler_quoted(char *stringa, t_parser *pars, t_shell *shell);

/*QUOTED TOKENIZER HELPERS*/
t_token		*check_prev(t_token *token);
void		join_tokens(t_token **node, t_token **prev);
void		join_tokens_values_when_no_space_between(t_parser *pars);
void		unpack_quoted_tokens(t_parser *pars, t_shell *shell);

/**EXPANSION HELPERS*/
char		*get_key_envp(char *envp_string);
char		*set_token_value_post_expansion(char *envp_string);
void		expand_env_var(char **token_value,t_shell *shell);

/*SYNTAX ANALIZER*/
int 		syntax_error_handler(t_token *head);
void change_non_special_tokens_to_word_tokens(t_token *head);

/*SYNTAX ANALIZER*/
int look_next_token_pipe(t_token *next);
int handle_pipe_synt_error_tokens(t_token *ptr);
int check_for_non_valid_char_list(t_token *ptr, char *non_valid_char);
int handle_greater_synt_error_tokens(t_token *ptr);
int handle_lesser_synt_error_tokens(t_token *ptr);


/**TOKEN MEMORY*/
void free_tokens(t_token *head);

#endif
