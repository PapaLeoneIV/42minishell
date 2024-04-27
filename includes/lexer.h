/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rileone <rileone@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 14:46:54 by rileone           #+#    #+#             */
/*   Updated: 2024/04/27 11:19:32 by rileone          ###   ########.fr       */
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
	LF_TOKEN,          // 2
	GREATER_TOKEN,     // 3 
	DGREATER_TOKEN,    // 4 
	LESSER_TOKEN,      // 5
	DLESSER_TOKEN,     // 6
	NULL_TOKEN,        // 7
    SING_QUOTES,       // 8
    DOUBLE_QUOTES,     // 9
};

enum CharType
{
    WHITESPACE,        // 0
    PIPELINE,          // 1
    REDIR_INPUT,       // 2
    REDIR_OUTPUT,      // 3
    REG_CHAR,          // 4
    SQUOTES,           // 5
    DQUOTES,           // 6
    ESCAPE_CHAR,       // 7
    DOLLAR_CHAR,       // 8
    F_SLASH,           // 9
    
    
    
};


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

/**
 * Frees the memory allocated for the token list.
 *
 * @param head The head of the token list.
 */
void token_free(t_token *head);


#endif
