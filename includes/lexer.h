/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rileone <rileone@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 14:46:54 by rileone           #+#    #+#             */
/*   Updated: 2024/04/28 19:36:16 by rileone          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

# include "./minishell.h"
# include "../libft/libft.h"
# include "../libft/gnl/get_next_line_bonus.h"
# include "../libft/printf/ft_printf.h"


typedef struct s_token_info {
    int     type;
    char    *string;
    int     start;
    int     end;
}               t_token_info;


typedef struct s_token
{
    char            *value; //
    int             type;   //
    struct s_token  *next;
}               t_token;

typedef struct parser
{
    int         state;
    int         char_type;
    int         count;
    int         start;
    t_token     *head;
    t_token     *token;
    t_token_info info;
}               t_parser;

enum State
{
    STATE_GENERAL,
    STATE_DQUOTE,
    STATE_SQUOTE,
    STATE_DOLLAR,
};

enum TokenType
{
	WORD_TOKEN,        // 0
	PIPE_TOKEN,        // 1
	GREATER_TOKEN,     // 3 
	DGREATER_TOKEN,    // 4 
	LESSER_TOKEN,      // 5
	DLESSER_TOKEN,     // 6
    SING_QUOTES_TOKEN,       
    DOUBLE_QUOTES_TOKEN,   
    DOLLAR_TOKEN,
    WHITESPACE_TOKEN,
    
};

enum CharType
{
    WHITESPACE_CHAR,    // 0
    PIPELINE_CHAR,      // 1
    REDIR_INPUT_CHAR,   // 2
    REDIR_OUTPUT_CHAR,  // 3
    REG_CHAR,           // 4
    SQUOTES_CHAR,       // 5
    DQUOTES_CHAR,       // 6
    DOLLAR_CHAR,        // 7
    DOLLAR_SPECIAL_CHAR,// 8
    DIGIT_CHAR,         // 9
    QUESTION_MARK_CHAR, // 10
    
    
};
/*TOKENIZER HELPERS*/

/**
 * @brief Determines the type of a character.
 *
 * This function takes a character as input and returns an integer representing its type.
 *
 * @param carattere The character to determine the type of.
 * @return An integer representing the type of the character.
 */
int get_char_type(char carattere);

/**
 * @brief Slices a single character token from a string.
 *
 * This function takes a string and a parser structure as input, and slices a single character token from the string.
 *
 * @param stringa The string to slice the token from.
 * @param pars The parser structure to store the sliced token.
 */
void slice_single_char_token(char *stringa, t_parser *pars);

/**
 * @brief Slices a token string from a string.
 *
 * This function takes a string and a parser structure as input, and slices a token string from the string.
 *
 * @param stringa The string to slice the token from.
 * @param pars The parser structure to store the sliced token.
 */
void slice_token_string(char *stringa, t_parser *pars);

/**
 * @brief Slices the end token from a string.
 *
 * This function takes a string and a parser structure as input, and slices the end token from the string.
 *
 * @param stringa The string to slice the token from.
 * @param pars The parser structure to store the sliced token.
 */
void slice_end_token(char *stringa, t_parser *pars);

/**
 * @brief Checks and changes the status based on a character.
 *
 * This function takes a state, a character, and a parser structure as input, and checks and changes the status based on the character.
 *
 * @param state A pointer to the state variable.
 * @param c The character to check.
 * @param pars The parser structure to update the status.
 */
void check_and_change_status(int *state, int c, t_parser *pars);



/**
 * Creates a token list from the given string.
 *
 * @param stringa The input string.
 * @param shell   The shell structure.
 * @return        0 if successful, -1 otherwise.
 */
int create_token_list(char *stringa, t_shell *shell);

/**
 * Sets the values of a token based on the given token info.
 *
 * @param token The token to set the values for.
 * @param info  The token info.
 */
void set_token_values(t_token *token, t_token_info *info);

/**
 * Creates a new token with the given data.
 *
 * @param data The data for the token.
 * @return     The newly created token.
 */
t_token *token_new(char *data);

/**
 * Adds a token to the end of the token list.
 *
 * @param head      The head of the token list.
 * @param new_token The token to add.
 */
void token_add_back(t_token **head, t_token *new_token);

/**
 * Returns the size of the token list.
 *
 * @param head The head of the token list.
 * @return     The size of the token list.
 */
int token_size(t_token *head);

/**
 * Clears the token list, freeing all allocated memory.
 *
 * @param head The head of the token list.
 */
void token_clear(t_token **head);



#endif
