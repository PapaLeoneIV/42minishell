/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgori <fgori@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 13:27:42 by fgori             #+#    #+#             */
/*   Updated: 2024/06/06 13:28:38 by fgori            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"minishell.h"

int	gnl2(char **line)
{
	char	*buf;
	int		i;
	int		n;
	char	ch;

	buf = (char *)ft_calloc(10000, 1);
	i = 1;
	n = 0;
	ch = 'c';
	while (i > 0 && ch != '\n')
	{
		i = read(0, &ch, 1);
		if (i < 0)
			return (free(buf), 0);
		buf[n] = ch;
		n++;
	}
	*line = ft_strdup(buf);
	if (!line)
		return (free(buf), 0);
	free(buf);
	return (n);
}

char **mtx_dup(char **mtx, int len)
{
	char **out;
	int i;

	i = 0;
	out = ft_calloc(len + 1 , sizeof(char *));
	while(i < len)
	{
		out[i] = ft_strdup(mtx[i]);
		i++;
	}
	return out;
}

void	freeall(char **mat)
{
	int	n;

	n = 0;
	while (mat[n])
	{
		free(mat[n]);
		mat[n] = NULL;
		n++;
	}
	free(mat);
}
