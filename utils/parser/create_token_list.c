/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_token_list.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rileone <rileone@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 14:36:02 by rileone           #+#    #+#             */
/*   Updated: 2024/04/26 16:55:49 by rileone          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/lexer.h"
#include "lexer.h"




    int get_char(char carattere)
    {
        if (carattere == ' ')
            return (WHITESPACE);
        else if (carattere == '|')
            return (PIPELINE);
        else if (carattere == '<')
            return (REDIR_INPUT);
        else if (carattere == '>')
            return (REDIR_OUTPUT);
        else if (carattere == '\'')
            return (SQUOTES);
        else if (carattere == '\"')
            return (DQUOTES);
        return (REG_CHAR);
    }

    int create_token_list(char *stringa, t_shell *shell)
    {
        int state = STATE_GENERAL;
        t_token *head;
        t_token *token;
        t_token_info info;
        int c;
        int i;
        int start = 0;

        head = NULL;
        i = 0;
        if (stringa == NULL || shell == NULL)
            return (-1);
        while (stringa[i] != '\0')
        {
            c = get_char(stringa[i]); // prendo il CharType del carattere
            if (state == STATE_GENERAL)
            {
                if (c == WHITESPACE || c == PIPELINE || c == REDIR_INPUT //se non incontro un REG_CHAR posso creare un token
                || c == REDIR_OUTPUT || c == SQUOTES || c == DQUOTES)
                {
                    if (i > start)  
                    {
                        token = token_new(NULL);

                        info = (t_token_info){WORD_TOKEN, stringa, start, i}; 
                        set_token_values(token, &info);
                        token_add_back(&head, token);
                        start = i + 1; //sposto start alla fine del token
                    }
                    if (c != WHITESPACE && c != SQUOTES && c != DQUOTES) //incotro un carattere speciale e me lo prendo
                    {
                        token = token_new(NULL);
                        info = (t_token_info){WORD_TOKEN, stringa, i, i + 1};
                        set_token_values(token, &info);
                        token_add_back(&head, token);
                        start = i + 1; //sposto start alla fine del token
                    }
                    if (c == SQUOTES || c == DQUOTES )   //cambio lo state machine per gestire le virgolette
                    {
                        if (c == SQUOTES)
                            state = STATE_SQUOTE;
                        else
                            state = STATE_DQUOTE;
                        start = i;
                    }
                }
            }
            else if ((c == SQUOTES && state == STATE_SQUOTE) || (c == DQUOTES && state == STATE_DQUOTE)) //se entro qui e' perche ho incontrato la seconda virgoletta
            {
                int Mquotes_arr[2] = {DOUBLE_QUOTES, SING_QUOTES};

                token = token_new(NULL);
                info = (t_token_info){Mquotes_arr[c == SQUOTES], stringa, start, i + 1};
                set_token_values(token, &info);
                token_add_back(&head, token);
                start = i + 1;
                state = STATE_GENERAL;   //resetto lo state machine
            }
            if (stringa[i + 1] == '\0' && i > start)  //prendo l ultimo token
            {
                token = token_new(NULL);
                info = (t_token_info){WORD_TOKEN, stringa, start, i + 1};
                set_token_values(token, &info);
                token_add_back(&head, token);
            }
            i++;
        }
        (void)shell;
        // Print token values
        token = head;
        while (token != NULL) {
            printf("%s\n", token->value);
/*             printf("%d\n", token->type); */
            token = token->next;
        }
    return (0);
    }