/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_frequency.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rileone <rileone@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 15:23:13 by rileone           #+#    #+#             */
/*   Updated: 2024/04/14 13:58:46 by rileone          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

int	ft_get_frequency(t_hash_map *map, int key)
{
	int		index;
	t_item	*current;

	index = ft_hash_fn(key, map->size);
	current = map->array[index];
	while (current != NULL)
	{
		if (current->key == key)
			return (current->value);
		current = current->next;
	}
	return (0);
}
