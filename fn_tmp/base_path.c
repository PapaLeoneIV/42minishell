/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   base_path.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rileone <rileone@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 16:21:45 by fgori             #+#    #+#             */
/*   Updated: 2024/05/22 22:17:31 by rileone          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//cd comand funtion//
void	cd_path(char **mtx)
{
	if (mtx_count_rows(mtx) > 2)
	{
		perror("ERROR\ntoo many arguments");
		return ;
	}
	/**va implementata la logica per tornare indietro con ".."
	 * penso che basti trimmare il path fino allo / precedente a meno
	 * che non sei gia nella root directory "/"
	*/
	chdir(mtx[1]);
}

void	pwd_path(void)
{
	char	*path;

	path = getcwd(NULL, 0);
	printf("%s\n", path);
	free(path);
}

char	*trimming(char *big, char *removed)
{
	int	i;

	i = 0;
	while (removed[i])
		i++;
	//if (!removed[i])
	//	return (NULL);
	i++;
	return(&big[i]);
}

void	echo_path(char **str)
{
	int		i;
	short	j;

	i = 1;
	j = 1;
	/**qui bisogna vedere se lo /n deve essere necessariamente attaccato al comando echo o
	 * se puo stare anche altrove nel comando 
	*/
	if (ft_strncmp(str[1], "-n", ft_strlen(str[1])) == 0)
	{
		i++;
		j = 0;
	}	
	while (str[i])
	{
		printf("%s", str[i]);
		if (str[i + 1])
			printf(" ");
		i++;
	}
	if (j != 0)
		printf("\n");
	/**va liberata anche il resto della matrice
	 * Update: aspettiamo di capire che cosa ci passiamo di preciso
	*/
	free(str);
	return ;
}

void	env_path(t_env	**env)
{
	t_env	*tmp;

	tmp = (*env);
	while (tmp)
	{
		if (tmp->esistence == 0)
			printf("%s=%s\n", tmp->head, tmp->body);
		tmp = tmp->next;
	}
}
//cd comand funtion end//