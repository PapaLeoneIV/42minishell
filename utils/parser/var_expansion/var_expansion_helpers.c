/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_expansion_helpers.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rileone <rileone@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/05 14:50:13 by rileone           #+#    #+#             */
/*   Updated: 2024/06/25 11:22:57 by rileone          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/lexer.h"

/* char *get_key_envp(char *envp_string)
{
	char *key;
	int end;

	end = ft_strchri_gnl(envp_string, '=');;
	key = ft_substr(envp_string, 0, end);
	return (key);
}
 */

char *set_token_value_post_expansion(char *envp_string)
{
	char *out;
	int end;
	int start;
	
	end = ft_strlen(envp_string);
	start = ft_strchri_gnl(envp_string, '=');
	out = ft_substr(envp_string, start + 1, end);
	if (out == NULL)
		return (NULL);
	return (out);
}
/* void expand_env_var(char **token_value, t_shell *shell)
{
	int envp_len;
	int i;
	char *pathKey;
	char *tmp;
	
	i = 0;
	envp_len = mtx_count_rows(shell->env[0]->env_mtx);
	while(i < envp_len)
	{
		pathKey = get_key_envp(shell->env[0]->env_mtx[i]);
		if (!strcmp(*token_value + 1, pathKey))
		{
			free(pathKey);
			pathKey = NULL;
			tmp = *token_value;		
			*token_value = set_token_value_post_expansion(shell->env[0]->env_mtx[i]);
			free(tmp);
			return ; 
		}
		free(pathKey);
		i++;
	}
    free(*token_value);
    *token_value = NULL;
	return ;
} */


void	expand_env_var(t_token **token, char **token_value, t_shell *shell)
{
	char	*tmp;
	t_env	*ptr;

	ptr = shell->env[0];
	while (ptr)
	{
		if (!strncmp(ptr->head, (*token_value + 1), ft_strlen(ptr->head)))
		{
			tmp = *token_value;
			*token_value = ft_strdup(ptr->body);
			free(tmp);
			return ;
		}
		ptr = ptr->next;
	}
	free(*token_value);
	*token_value = NULL;
	free(*token);
	*token = NULL;
	return ;
}