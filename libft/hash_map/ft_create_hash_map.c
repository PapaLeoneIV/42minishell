/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_create_hash_map.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rileone <rileone@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 15:23:13 by rileone           #+#    #+#             */
/*   Updated: 2024/04/14 13:48:48 by rileone          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

t_hash_map	*ft_create_hash_map(int size)
{
	t_hash_map	*map;
	int			i;

	i = 0;
	map = (t_hash_map *)malloc(sizeof(t_hash_map));
	map->size = size;
	map->n_item = 0;
	map->array = (t_item **)calloc(size, sizeof(t_item *));
	while (i < size)
	{
		map->array[i] = NULL;
		i++;
	}
	return (map);
}

/* 
int	main(void)
{
    t_hash_map * map;
    int i = 0;
    map = ft_create_t_hash_map (10);
    while(i < 10)
    {
        printf("%p\n", (void *)map->array[i]);
        i++;
    }
} */
