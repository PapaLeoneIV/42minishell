/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dictionary_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rileone <rileone@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 16:41:40 by rileone           #+#    #+#             */
/*   Updated: 2024/06/27 16:41:32 by rileone          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

/* t_dictnode	*newNode(void)
{
	t_dictnode	*newnode;

	newnode = calloc(1, sizeof(t_dictnode));
	if (!newnode)
		return (NULL);
	newnode->key = NULL;
	newnode->value = NULL;
	newnode->next = NULL;
	return (newnode);
} */
/* 
void	setNodeKey(t_dictNode **node, char *key)
{
	if (node == NULL || key == NULL)
		perror("key not existing!");
	(*node)->key = key;
}

void	setNodeValue(t_dictNode **node, char *value)
{
	if (node == NULL || value == NULL)
		perror("value not existing!");
	(*node)->value = value;
}

void	addNode(t_dictNode **node, char *key, char *value)
{
	t_dictNode	*current;
	t_dictNode	*newnode;

	newnode = newNode();
	setNodeKey(&newnode, key);
	setNodeValue(&newnode, value);
	if (*node == NULL)
		*node = newnode;
	else
	{
		current = *node;
		while (current->next != NULL)
			current = current->next;
		current->next = newnode;
	}
}

char	*getNodeValWithKey(t_dictNode *node, char *key)
{
	if (!node || key == NULL)
		return (NULL);
	while (key != node->key)
	{
		if (key == node->key)
			return (node->value);
		node = node->next;
	}
	return (NULL);
}

char	*getNodeKeyWithValue(t_dictNode *node, char *value)
{
	if (!node || value == NULL)
		return (NULL);
	while (value != node->value)
	{
		if (value == node->value)
			return (node->key);
		node = node->next;
	}
	return (NULL);
}
void	printDictionary(t_dictNode *dict)
{
	t_dictNode	*current;

	current = dict;
	while (current != NULL)
	{
		printf("Key: %s, Value: %s\n", current->key, current->value);
		current = current->next;
	}
} */
/* int main()
{
    t_dictNode *dict;
	int		i;
	char	*lista[5];
	char	*array[5];

    i = 0;
    dict = NULL;
    lista[5] = {"cat", "ls", "|", "grep", "-ag"};
    array[5] = {"WORD", "WORD", "PIPE", "WORD", "FLAG"};
    while (i < 5)
    {
        addNode(&dict, lista[i], array[i]);
        i++;
    }
    printDictionary(dict);
}
  */
/***
 * devo leggere il prompt
 * e da li generare una lista di Parole rappresentative del prompt
 * 
*/