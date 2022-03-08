/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_keyval_lst.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gvitor-s <gvitor-s>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/08 18:26:43 by gvitor-s          #+#    #+#             */
/*   Updated: 2022/03/08 18:40:11 by gvitor-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils_keyval_lst.h"
#include "hashtable.h"
#include "libft.h"

struct s_keyval	*new_node_of_bucket(char *key, char *value)
{
	struct s_keyval	*new;

	new = malloc(sizeof(struct s_keyval));
	if (NOT new)
		return (NULL);
	new->val = value;
	new->key = key;
	return (new);
}

struct s_keyval	*last_node_of_bucket(struct s_keyval *bucket)
{
	while (bucket->next)
	{
		bucket = bucket->next;
	}
	return (bucket);
}

void	keyval_add_back(struct s_keyval **bucket, struct s_keyval *new)
{
	if (NOT (*bucket))
		*bucket = new;
	else
		last_node_of_bucket(*bucket)->next = new;
}
