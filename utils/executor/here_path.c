/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_path.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgori <fgori@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 14:57:29 by fgori             #+#    #+#             */
/*   Updated: 2024/07/04 11:31:16 by fgori            ###   ########.fr       */
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

int	prompt_here(int fd, t_redir **redir, t_shell *shell)
{
	char	*input_here;

	signal(SIGINT, handle_signal);
	input_here = readline(">");
	if (input_here == NULL || g_status_code == 130)
	{
		free(input_here);
		return (-1);
	}
	if (ft_strncmp(input_here, (*redir)->filename, ft_strlen((*redir)->filename)) == 0)
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
				return (close(fd), -2);
		}
		close(fd);
		(*redir)->type_of_redirection = LESSER_TOKEN;
		fd = 0;
	}
	return (fd);
}
