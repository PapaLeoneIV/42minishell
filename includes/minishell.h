/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rileone <rileone@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/21 14:05:00 by rileone           #+#    #+#             */
/*   Updated: 2024/05/01 15:27:22 by rileone          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H


# include "../libft/libft.h"
# include "../libft/gnl/get_next_line_bonus.h"
# include "../libft/printf/ft_printf.h"
# include <readline/readline.h>
# include <readline/history.h>


typedef struct s_shell
{
    char        *line;
    char        **envp;
    
}   t_shell;

/**ENV FUNCTIONS*/

void split_envp(t_shell *shell, char *envp);
void set_env(t_shell *shell, char **envp);

/**READ FUNCTION*/
void read_from_stdin(t_shell *shell);




#endif