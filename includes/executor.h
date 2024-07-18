/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgori <fgori@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 19:27:19 by rileone           #+#    #+#             */
/*   Updated: 2024/07/18 13:48:39 by fgori            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTOR_H
# define EXECUTOR_H

# include "./minishell.h"

typedef struct s_shell		t_shell;
typedef struct s_command	t_command;
typedef struct s_redir		t_redir;
typedef struct s_parser		t_parser;
typedef struct s_token_info	t_token_info;
typedef struct s_token		t_token;

char	**mtx_dup(char **mtx, int len);
int		open_redir(t_command *cmd, t_shell *shell, t_redir **redir, int flag);
char	*heredoc_tokenizer(char *input, t_shell *shell);
char	*rename(char *filename);
int		get_char_type_heredoc(char *str, t_parser *pars, int count);
void	general_state_handler_heredoc(char *input,
			t_parser *pars);
int		set_token_info_here(t_token_info *info, t_parser *pars, char *stringa);
char	*join_token_values(t_token *list);
int		slice_end_token_heredoc(char *stringa,
			t_parser *pars, t_shell *shell);
char	*take_path(t_env *path, char **tmp_cmd, t_command *cmd, t_shell *shell);
int		execute_cmd(t_shell *shell);
int		execution(t_command *cmd, t_env **env, t_shell *shell);
int		gnl2(char **line);
int		check_head(char *str);
int		make_redir(t_shell *shell, t_command *cmd);
int		heardoc_path(t_redir **redir, t_shell *shell, t_command *cmd);
int		set_pip(t_command *cmd, int *pip);
int		exit_path(t_command *cmd, t_shell *shell);
int		ft_biltin(t_command *cmd, t_env **lst, t_shell *shell);
int		is_a_biltin(char **tmp);
void	freeall(char **mat);
void	multi_freeall(char **tmp_env, char **tmp_cmd,
			t_shell *shell, char *str);
char	*ft_access(char **open_path, char *cmd);
int		tm_close(int tm_in, int tm_out, int flag);
void	write_exit(char *str, char *cmd, char *finish);
void	write_line(int cat, t_shell *shell);
int		cat_check(t_command *cmd);
void	exev_error(t_shell *shell, char *supp);
void	write_clean(char *cmd, t_shell *shell);
int		take_last_pid(t_shell *shell);
int		error_fd_managemnt(t_command *cmd,
			t_shell *shell, t_redir *tmp, int flag);
void	ft_unlink(t_command *cmd);

#endif
