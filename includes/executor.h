/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rileone <rileone@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 19:27:19 by rileone           #+#    #+#             */
/*   Updated: 2024/05/24 19:54:21 by rileone          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef EXECUTOR_H
#define EXECUTOR_H

#include "./minishell.h"

typedef struct s_shell t_shell;
typedef struct s_command t_command;
typedef struct s_redir t_redir;


int	execute_cmd(t_shell **shell);
int	execution(t_command *cmd, t_env **env);
int	list_of_in(t_redir *dir);
int	list_of_out(t_redir *dir);


#endif
