/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgori <fgori@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 10:42:51 by fgori             #+#    #+#             */
/*   Updated: 2024/06/06 09:32:57 by fgori            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTIN_H
# define BUILTIN_H

# include <readline/readline.h>
# include <readline/history.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <signal.h>
# include <sys/stat.h>
# include <dirent.h>
# include <string.h>
# include <termios.h>
# include <termcap.h>
# include "../libft/libft.h"
# include "./minishell.h"

typedef struct s_env t_env;
typedef struct s_command t_command;
typedef struct s_shell t_shell;
typedef struct s_redir t_redir;

void	add_node_to_env_struct(t_env **lst, t_env *new);
char	*get_directory_path(void);
int		cd_path(char **mtx, t_env **env);
int		pwd_path(void);
char	*trimming(char *big, char *removed);
int		echo_path(char **str);
t_env	**get_env_info(char *en[]);
int		env_path(t_env	**env);
int		export_path(t_env **lst, char **mtx);
t_env	*lst_new_env(char *str, char **en);
t_env	*find_node(t_env **lst, char *str);
void    clean_env_lst(t_env **lst);
void    clean_env_node(t_env **lst);
int		unset_path(t_env **lst, char **mtx);
void	clean_redir(t_redir **redir);
void	clean_cmd_node(t_command **cmd);
void	clean_all(t_shell *shell, int flag);

#endif