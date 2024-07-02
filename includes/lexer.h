/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgori <fgori@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 14:46:54 by rileone           #+#    #+#             */
/*   Updated: 2024/07/02 11:30:50 by fgori            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
#define LEXER_H

#include "./minishell.h"

typedef struct s_command t_command;
typedef struct s_shell t_shell;
typedef struct s_redir t_redir;

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

typedef struct s_redir
{
	int					in;
	int					out;
	int					type_of_redirection;
	int					heredoc_expansion;
	char*				filename;
	struct s_redir		*next;
} t_redir;

typedef struct s_command
{
	char 				**cmd;
	struct s_redir		**redirection_info;
	int					pip[2];
	int					in;
	int					out;
	int					fd_change;
	char				*here;
	int					cmd_id;
	int					fork_id;
	struct s_command	*next;
	struct s_command	*prev;
} 			t_command;

enum bool
{
	false,
	true, 
};

enum error_handling
{
	ERROR,
	SUCCESS,
};

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
	HERDOC_FILENAME_WITHQUOTES, //10

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
	TILDE_CHAR,			//11
	TERMINATOR_CHAR,		
	NEWLINE_CHAR,
};

typedef struct s_parser_redirection
{
	t_command *cmd_node;
	t_token *tmp_list;
	t_token *node;
	t_token *ptr;
	int check;
	int i;

} t_parser_red;

/*TOKEN CREATION METHODS*/
void		set_token_values(t_token *token, t_token_info *info);
t_token		*token_new(char *data);
void		token_add_back(t_token **head, t_token *new_token);
void		token_print(t_token *head);

/*TOKENIZER MAIN FUNCTIONS*/
t_token		*tokenize_input(char *input, t_shell *shell);
int			create_token_list(char *stringa, t_shell *shell, t_parser *pars);

/*TOKENIZER HELPERS*/
int			look_for_another_redirect(char *stringa, t_parser *pars);
int			valid_regchar(char *str, t_parser *pars);
int			get_char_type(char *str, t_parser *pars, int count);

/*TOKENIZER HELPERS(SLICE METHODS)*/
void		slice_single_char_token(char *stringa, t_parser *pars, t_shell *shell);
void		slice_redirect_token(char *stringa, t_parser *pars);
void		slice_token_string(char *stringa, t_parser *pars);
int			slice_end_token(char *stringa, t_parser *pars, t_shell *shell);
void 		slice_token_string_doll_spec_case(char *stringa, t_parser *pars);

/*TOKENIZER HELPERS(STATE HANDLERS)*/
void		general_state_handler(char *stringa, t_parser *pars, t_shell *shell);
void		dollar_state_handler(char *stringa, t_parser *pars, t_shell *shell);
void		quoted_state_handler(char *stringa, t_parser *pars);
void		check_and_change_status(int *state, int c, t_parser *pars);

/*QUOTED TOKENIZER HELPERS*/
int			valid_regchar_quoted(char c);
int			get_char_type_quoted(char c);
t_parser	*tokenize_quoted_values(t_token *node, t_shell *shell);
void		general_state_handler_quoted(char *stringa, t_parser *pars, t_shell *shell);
void		dollar_state_handler_quoted(char *stringa, t_parser *pars, t_shell *shell);

/*QUOTED TOKENIZER HELPERS*/
t_token		*check_prev(t_token *token);
void		join_tokens(t_token **node, t_token **prev);
void		join_tokens_values_when_no_space_between(t_parser *pars);
void		unpack_quoted_tokens(t_token **head, t_shell *shell);

/**EXPANSION HELPERS*/
char		*get_key_envp(char *envp_string);
char		*set_token_value_post_expansion(char *envp_string);
void		expand_env_var(t_token **token, char **token_value,t_shell *shell);

/*SYNTAX ANALIZER*/
int 		syntax_error_handler(t_token **head);
void 		change_non_special_tokens_to_word_tokens(t_token *head);
int			check_for_non_valid_char_list(t_token *ptr, char *non_valid_char);
void		change_non_special_tokens_to_word_tokens(t_token *head);
void		remove_whitespaces(t_token **head);

/*SYNTAX ANALIZER*/
int			handle_pipe_synt_error_tokens(t_token *ptr);
int			handle_greater_synt_error_tokens(t_token *ptr);
int			handle_lesser_synt_error_tokens(t_token *ptr);
int			headle_heredoc_syntax_error_tokens(t_token *ptr);
int			handle_redirout_synt_error_tokens(t_token *ptr);

/**TOKEN MEMORY*/
void		free_tokens(t_token *head);
void		remove_null_tokens(t_parser *pars);
void		redirection_clear(t_token **head);

/**REDIRECTION PARSING*/
int			parse_redirections(t_token *head, t_shell *shell);
int			handle_redirection_logic(t_token *node, t_command *cmd_node);
int			remove_redir(t_token **redir);
t_token		*split_command_based_on_pipes(t_token **ptr);
int			count_pipes(t_token *head);
t_token		*look_tokens_ahead(t_token *current);

/**REDIRECTION PARSING (HELPERS)*/
t_redir		*new_redir_node(int type, char *value, int flag);
void		add_back_redirections(t_redir **lst, t_redir *node);
t_command	*new_command(int counter);
void		add_back_commands(t_command **lst, t_command *node);
char		**from_lst_to_mtx(t_token *head);

#endif
