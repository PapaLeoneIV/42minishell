/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_path.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 14:57:29 by fgori             #+#    #+#             */
/*   Updated: 2024/07/13 13:11:41 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	here_expansion(t_redir **redir, t_shell *shell, char *input, int fd)
{
	char	*tmp;
	char	*temp;

	if ((*redir)->heredoc_expansion)
	{
		tmp = heredoc_tokenizer(input, shell);
		temp = ft_strjoin(tmp, "\n");
		free(tmp);
		ft_putstr_fd(temp, fd);
		free(temp);
	}
	else
	{
		temp = ft_strjoin(input, "\n");
		ft_putstr_fd(temp, fd);
		free(temp);
	}
}

int	ft_strcmp(const char *s1, const char *s2)
{
	if (!s1 || !s2)
		return (1);
	while (*s1 && *s1 == *s2)
	{
		s1++;
		s2++;
	}
	return ((unsigned char)(*s1) - (unsigned char)(*s2));
}

int	prompt_here(int fd, t_redir **redir, t_shell *shell)
{
	char	*input_here;

	input_here = readline(">");
	if (input_here == NULL || g_status_code == 130)
	{
		free(input_here);
		return (-1);
	}
	if (ft_strlen(input_here) == ft_strlen((*redir)->filename) - 2 &&
			ft_strncmp(input_here, (*redir)->filename,
			ft_strlen((*redir)->filename) - 2) == 0)
	{
		free(input_here);
		return (0);
	}
	here_expansion(redir, shell, input_here, fd);
	return (1);
}

int	heardoc_path(t_redir **redir, t_shell *shell)
{
	int	fd;
	int	ex;

	ex = 1;
	fd = open((*redir)->filename, O_TRUNC | O_CREAT | O_RDWR, 0777);
	if (fd < 0)
		return (perror("ERROR"), ERROR);
	while ((*redir) && (*redir)->type_of_redirection == HEREDOC_TOKEN)
	{
		while (ex)
		{
			ex = prompt_here(fd, redir, shell);
			if (ex == -1 && g_status_code != 130)
				write_exit("minishell:", "warning: ",
					"here-document delimited by end-of-file\n");
			if (ex == -1 || g_status_code == 130)
			{
				unlink((*redir)->filename);
				return (close(fd), -2);
			}
		}
		close(fd);
		(*redir)->type_of_redirection = LESSER_TOKEN;
	}
	return (fd);
}

int	error_fd_managemnt(t_command *cmd, t_shell *shell, t_redir *tmp, int flag)
{
	if (cmd->out == -1 || cmd->in == -1)
	{
		if (tmp && tmp->next)
			open_redir(cmd, shell, &tmp->next, ERROR);
		if (g_status_code != 130 && flag)
			write_exit(tmp->filename, " : No such file or directory\n", NULL);
		else
			return (-2);
		return (ERROR);
	}
	else if (cmd->in == -2)
	{
		cmd->in = -1;
		return (-2);
	}
	return (SUCCESS);
}
