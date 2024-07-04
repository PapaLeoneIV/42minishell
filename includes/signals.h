/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rileone <rileone@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/01 11:37:23 by rileone           #+#    #+#             */
/*   Updated: 2024/07/04 10:39:05 by rileone          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SIGNALS_H
# define SIGNALS_H

# include "./minishell.h"

typedef struct s_shell	t_shell;

void	handle_signal(int signum);
void	handle_ctrl_d(t_shell *shell, char *input);

#endif
