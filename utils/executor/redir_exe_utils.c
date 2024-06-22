/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_exe_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rileone <rileone@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 13:26:16 by fgori             #+#    #+#             */
/*   Updated: 2024/06/22 15:36:35 by rileone          ###   ########.fr       */
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
			fd = open((*dir)->filename, O_TRUNC | O_CREAT | O_RDWR, 0777);
		else
			fd = open((*dir)->filename, O_APPEND | O_CREAT | O_RDWR, 0777);
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
			write(2, (*dir)->filename, ft_strlen((*dir)->filename));
			write(2, " : No such file or directory\n", 30);
			(*dir) = (*dir)->next;
			return (-1);
		}
		if ((*dir)->next && (*dir)->next->type_of_redirection == LESSER_TOKEN)
			close(fd);
		(*dir) = (*dir)->next;
	}
	return (fd);
}

int	check_valid_line(char *line)
{
	if (line && *line == '\0')
		return (ERROR);
	return (SUCCESS);
}

int	prompt_here(char *line, int fd, t_redir **redir, t_shell *shell)
{
	char	*tmp;
	char	*input_here;

	signal(SIGINT, handle_signal);
	input_here = readline(">");
	if (input_here == NULL || g_status_code == 130)
	{
		free(input_here);
		return (-1);
	}
	if (ft_strncmp(input_here, (*redir)->filename, ft_strlen(input_here)) == 0)
	{
		free(input_here);
		return (0);
	}
	if ((*redir)->heredoc_expansion)
	{
		char	*temp;
		tmp = heredoc_tokenizer(input_here, shell);
		temp = ft_strjoin(tmp, "\n");
		free(tmp);
		ft_putstr_fd(temp, fd);
		free (temp);
	}
	else
	{
		char	*temp;
		temp = ft_strjoin(line, "\n");
		free(line);
		ft_putstr_fd(temp, fd);
		free (temp);
	}
	free(line);
	return (1);
}

int	heardoc_path(t_redir **redir, t_shell *shell)
{
	int		fd;
	char	*line;
	int		ex;

	ex = 1;
	line = NULL;
	fd = open((*redir)->filename, O_TRUNC | O_CREAT | O_RDWR, 0777);
	if (fd < 0)
		return (perror("ERROR"), ERROR);
	while ((*redir) && (*redir)->type_of_redirection == HEREDOC_TOKEN)
	{
		while (ex)
		{
			ex = prompt_here(line, fd, redir, shell);
			if (ex == -1 && g_status_code != 130)
				write(2, "\nminishell: warning: here-document delimited by end-of-file\n", 61);
			if (ex == -1 || g_status_code == 130)
				return (close(fd), -2);
		}
		close(fd);
		(*redir)->type_of_redirection = LESSER_TOKEN;
		fd = 0;
	}
	return (fd);
}

int	open_redir(t_command *cmd, t_shell *shell)
{
	t_redir	*tmp;

	if (!cmd->redirection_info)
		return (1);
	tmp = (*cmd->redirection_info);
	while (tmp)
	{
		if (!tmp)
			break ;
		if (tmp->type_of_redirection == GREATER_TOKEN
			|| tmp->type_of_redirection == REDIR_OUT_TOKEN)
			cmd->out = list_of_out(&tmp);
		else if (tmp->type_of_redirection == LESSER_TOKEN)
			cmd->in = list_of_in(&tmp);
		else if (tmp->type_of_redirection == HEREDOC_TOKEN)
		{
			if (cmd->here)
				unlink(cmd->here);
			cmd->here = tmp->filename;
			cmd->in = heardoc_path(&tmp, shell);
		}
		if (cmd->out == -1 || cmd->in == -1)
			return (ERROR);
		else if (cmd->in == -2)
			return (-2);
	}
	return (1);
}
