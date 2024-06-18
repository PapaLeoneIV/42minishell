/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgori <fgori@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 19:27:19 by rileone           #+#    #+#             */
/*   Updated: 2024/06/18 12:03:06 by fgori            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef EXECUTOR_H
#define EXECUTOR_H

#include "./minishell.h"

typedef struct s_shell t_shell;
typedef struct s_command t_command;
typedef struct s_redir t_redir;


int		execute_cmd(t_shell *shell);
int		execution(t_command *cmd, t_env **env,  t_shell *shell);
int		list_of_in(t_redir **dir);
int		list_of_out(t_redir **dir);
void	freeall(char **mat);
char	 *heredoc_tokenizer(char *input, t_shell *shell);
int		gnl2(char **line);
char	 **mtx_dup(char **mtx, int len);
void	freeall(char **mat);
int		list_of_out(t_redir **dir);
int		list_of_in(t_redir **dir);
int		heardoc_path(t_redir **redir, t_shell *shell);
void	tm_close(int tm_in, int tm_out, int flag);
int		set_pip(t_command *cmd, int *pip);
int		open_redir(t_command *cmd, t_shell *shell);
int		exit_path(t_command *cmd, t_shell *shell);
int		ft_biltin(char **tmp, t_env **lst, t_shell *shell);
int		is_a_biltin(char **tmp);
char	*ft_access(char **open_path, char *cmd);
int		check_head(char *str);

#endif
