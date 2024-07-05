/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rileone <rileone@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/21 14:05:00 by rileone           #+#    #+#             */
/*   Updated: 2024/07/04 13:51:48 by rileone          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/libft.h"
# include "../libft/gnl/get_next_line_bonus.h"
# include "../libft/printf/ft_printf.h"
# include <readline/readline.h>
# include <readline/history.h>
# include <signal.h>
# include <sys/ioctl.h>

# include "signals.h"
# include "./lexer.h"
# include "./builtin.h"
# include "./executor.h"

typedef struct s_token		t_token;
typedef struct s_command	t_command;
typedef struct s_shell		t_shell;
typedef struct s_redir		t_redir;

extern int					g_status_code;

typedef struct s_env
{
	char			**env_mtx;
	char			*head;
	char			*body;
	short			esistence;
	struct s_env	*next;
	struct s_env	*prev;
}	t_env;

typedef struct s_shell
{
	char		*line;
	int			shell_pip[2];
	t_command	**cmd_info;
	t_env		**env;
	int			status;
}	t_shell;

/**READ FUNCTION*/
void	read_from_stdin(t_shell *shell, char **envp);

#endif