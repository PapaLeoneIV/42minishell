/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rileone <rileone@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/01 11:37:23 by rileone           #+#    #+#             */
/*   Updated: 2024/06/01 11:47:50 by rileone          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef SIGNALS_H
#define SIGNALS_H

#include "./minishell.h"

extern struct sigaction signal_g; 
typedef struct s_shell t_shell;

void set_signal_handler(struct sigaction *signal_g);
void handle_signal(int signum);
void handle_ctrl_d(t_shell *shell, char *input);


#endif
