/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgori <fgori@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 19:27:19 by rileone           #+#    #+#             */
/*   Updated: 2024/07/02 12:00:00 by fgori            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTOR_H
# define EXECUTOR_H

# include "./minishell.h"

typedef struct s_shell		t_shell;
typedef struct s_command	t_command;
typedef struct s_redir		t_redir;

char	**mtx_dup(char **mtx, int len);
char	*heredoc_tokenizer(char *input, t_shell *shell);
char	*take_path(t_env *path, char **tmp_cmd, t_command *cmd);
int		execute_cmd(t_shell *shell);
int		execution(t_command *cmd, t_env **env, t_shell *shell);
int		gnl2(char **line);
int		check_head(char *str);
int		list_of_out(t_redir **dir);
int		list_of_in(t_redir **dir);
int		make_redir(t_shell *shell, t_command *cmd);
int		heardoc_path(t_redir **redir, t_shell *shell);
int		set_pip(t_command *cmd, int *pip);
int		open_redir(t_command *cmd, t_shell *shell);
int		exit_path(t_command *cmd, t_shell *shell, int flag);
int		ft_biltin(t_command *cmd, t_env **lst, t_shell *shell);
int		is_a_biltin(char **tmp);
void	freeall(char **mat);
void	multi_freeall(char **tmp_env, char **tmp_cmd, t_shell *shell);
char	*ft_access(char **open_path, char *cmd);
void	tm_close(int tm_in, int tm_out, int flag);
void	write_exit(char *str, char *cmd, char *finish);
void	close_all_fd(int flag);
#endif
