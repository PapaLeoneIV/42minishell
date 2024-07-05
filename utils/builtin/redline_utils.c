/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redline_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rileone <rileone@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 16:16:15 by fgori             #+#    #+#             */
/*   Updated: 2024/07/05 10:55:58 by rileone          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	cont_slash(char *s)
{
	int	i;
	int	n;

	i = 0;
	n = 0;
	while (s[i])
	{
		if (s[i] == '/')
			n++;
		i++;
	}
	return (n);
}

static char	*trim_current_path(char *path)
{
	int	count;
	int	n_slash;
	int	direct_depth;

	n_slash = cont_slash(path);
	count = 0;
	direct_depth = 0;
	if (n_slash <= 3)
		return (NULL);
	else
	{
		count = ft_strlen(path) - 1;
		while (count-- > 0)
		{
			if (path[count] == '/')
				direct_depth++;
			if (direct_depth == 3)
				break ;
		}
	}
	return (ft_substr(path, count, ft_strlen(path)));
}

char	*get_directory_path(void)
{
	char	*path;
	char	*trimmed_path;
	char	*tmp;

	path = getcwd(NULL, 0);
	trimmed_path = trim_current_path(path);
	if (!trimmed_path)
		trimmed_path = ft_strdup(path);
	free(path);
	tmp = ft_strjoin(trimmed_path, " ");
	path = ft_strjoin("\033[0;32mminishell~:\033[0m ../",
			tmp);
	free(trimmed_path);
	free(tmp);
	return (path);
}
