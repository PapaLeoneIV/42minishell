/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rileone <rileone@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 10:42:51 by fgori             #+#    #+#             */
/*   Updated: 2024/05/22 22:37:24 by rileone          ###   ########.fr       */
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


void	add_node_to_env_struct(t_env **lst, t_env *new);
char	*get_directory_path(void);
void	cd_path(char **mtx);
void	pwd_path(void);
char	*trimming(char *big, char *removed);
void	echo_path(char **str);
t_env	**get_env_info(char *en[]);
void	env_path(t_env	**env);
void	export_path(t_env **lst, char **mtx);
t_env	*lst_new_env(char *str, char **en);

void    clean_env_lst(t_env **lst);
void    clean_env_node(t_env **lst);
void	unset_path(t_env **lst, char **mtx);

#endif