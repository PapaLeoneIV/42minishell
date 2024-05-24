/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rileone <rileone@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/21 14:05:00 by rileone           #+#    #+#             */
/*   Updated: 2024/05/24 19:31:16 by rileone          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H


# include "../libft/libft.h"
# include "../libft/gnl/get_next_line_bonus.h"
# include "../libft/printf/ft_printf.h"
# include <readline/readline.h>
# include <readline/history.h>


#include "./lexer.h"
#include "./builtin.h"
#include "./executor.h"

typedef struct s_token t_token;
typedef struct s_command t_command;


typedef struct s_env
{
	char			**env;
	char			*head;
	char			*body;
	short			esistence;
	struct s_env	*next;
	struct s_env	*prev;
}	t_env;

typedef struct s_shell
{
    char        *line;
    char        **envp;
    t_command   **cmd_info;
    t_env       **env;
}   t_shell;

/**ENV FUNCTIONS*/

void split_envp(t_shell *shell, char *envp);
void set_env(t_shell *shell, char **envp);
char *path_string(t_shell *shell);
char **return_path_string_splitted(t_token **head, t_shell *shell);


/**READ FUNCTION*/
void read_from_stdin(t_shell *shell);




#endif