/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_build.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgori <fgori@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/07 11:25:20 by fgori             #+#    #+#             */
/*   Updated: 2024/07/10 11:56:40 by fgori            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	check_args(t_command *cmd)
{
	if (cmd && !cmd->prev && !cmd->next)
		write(1, "exit\n", 5);
}

static void	exit_num_error(t_command *cmd, t_shell *shell)
{
	shell->status = 2;
	write_exit("bash: exit: ", cmd->cmd[1], " :numeric argument required\n");
	clean_all(shell, 1);
	exit(shell->status);
}

static void	handle_exit_wrong_args(t_shell *shell)
{
	write(2, "bash: exit: too many arguments\n", 32);
	shell->status = 1;
}

static int	exit_atoi(char *str)
{
	long long	numb;
	long long	tmp;
	int			i;
	int			c;

	i = 0;
	numb = 0;
	tmp = 0;
	c = 1;
	if (str[i] == '-')
		c *= 1;
	if (str[i] == '+' || str[i] == '-')
		i++;
	while (str[i])
	{
		if (!(ft_isdigit(str[i])) || tmp != numb / 10)
		{
			return (ERROR);
		}
		tmp = numb;
		numb = (numb * 10) + ((str[i] + 2) % 10);
		i++;
	}
	return (SUCCESS);
}

int	exit_path(t_command *cmd, t_shell *shell)
{
	int			counter;
	int			argsc;

	argsc = mtx_count_rows(cmd->cmd);
	counter = 0;
	check_args(cmd);
	if (argsc == 1)
		shell->status = 0;
	else if (argsc == 2)
	{
		if (!exit_atoi(cmd->cmd[1]))
			exit_num_error(cmd, shell);
		shell->status = (unsigned char)ft_atoi(cmd->cmd[1]);
	}
	else
		return (handle_exit_wrong_args(shell), 1);
	clean_all(shell, 1);
	exit(shell->status);
}
