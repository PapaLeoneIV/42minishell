/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_expansion_helpers.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgori <fgori@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/05 14:50:13 by rileone           #+#    #+#             */
/*   Updated: 2024/07/16 12:31:57 by fgori            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/lexer.h"

char	*set_token_value_post_expansion(char *envp_string)
{
	char	*out;
	int		end;
	int		start;

	end = ft_strlen(envp_string);
	start = ft_strchri_gnl(envp_string, '=');
	out = ft_substr(envp_string, start + 1, end);
	if (out == NULL)
		return (NULL);
	return (out);
}

void	expand_env_var(t_token **token, char **token_value, t_shell *shell)
{
	char	*tmp;
	t_env	*ptr;

	ptr = shell->env[0];
	while (ptr)
	{
		if (!strncmp(ptr->head, (*token_value + 1),
				ft_strlen(*token_value + 1) + 1))
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
