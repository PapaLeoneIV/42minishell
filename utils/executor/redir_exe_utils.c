/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_exe_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgori <fgori@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 13:26:16 by fgori             #+#    #+#             */
/*   Updated: 2024/06/06 13:58:48 by fgori            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	list_of_out(t_redir **dir)
{
	int	fd;
	int	redir;

	redir = (*dir)->type_of_redirection;
	while ((*dir))
	{
		if ((*dir)->type_of_redirection == GREATER_TOKEN)
			fd = open((*dir)->filename,  O_TRUNC | O_CREAT | O_RDWR, 0777);
		else
			fd = open((*dir)->filename,  O_APPEND | O_CREAT | O_RDWR, 0777);
		if (fd < 0)
		{
			printf("impossible to open: %s\n", (*dir)->filename);
			return (-1);
		}
		if ((*dir)->next && (*dir)->next->type_of_redirection == redir)
			close(fd);
		(*dir) = (*dir)->next;
	}
	return (fd);
}

int	list_of_in(t_redir **dir)
{
	int	fd;
	
	while ((*dir) && (*dir)->type_of_redirection == LESSER_TOKEN)
	{
		fd = open((*dir)->filename, O_RDONLY, 0777);
		if (fd < 0)
		{
			printf("%s: No such file or directory\n", (*dir)->filename);
			(*dir) = (*dir)->next;
			return(-1);
		}
		if ((*dir)->next && (*dir)->next->type_of_redirection == LESSER_TOKEN)
			close(fd);
		(*dir) = (*dir)->next;   
	}
	return (fd);
}

int	heardoc_path(t_redir **redir, t_shell *shell)
{
	int		fd;
	char	*line;
	char	*tmp;

	fd = open((*redir)->filename, O_TRUNC| O_CREAT | O_RDWR, 0777);
	if (fd < 0)
		return (perror("ERROR"), ERROR);
	while ((*redir) && (*redir)->type_of_redirection == HEREDOC_TOKEN)
	{
		while (1)
		{
			ft_putchar_fd('>', 1);
			if (gnl2(&line) && line[ft_strlen((*redir)->filename)] == '\n'
				&& ft_strncmp(line, (*redir)->filename, ft_strlen((*redir)->filename)) == 0)
				{
					free(line);
					break ;
				}
			if ((*redir)->heredoc_expansion)
			{
				tmp = heredoc_tokenizer(line, shell);
				ft_putstr_fd(tmp, fd);
				free (tmp);
			}
			else
				ft_putstr_fd(line, fd);
			free(line);
		}
		close(fd);
		(*redir)->type_of_redirection = LESSER_TOKEN;
		fd = 0;
	}
	return (fd);
}
