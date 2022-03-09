/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hashtable.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gvitor-s <gvitor-s@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/05 16:48:33 by gvitor-s          #+#    #+#             */
/*   Updated: 2022/03/09 14:05:03 by gvitor-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hashtable.h"
#include "libft.h"
#include <stdlib.h>
#include <errno.h>
#include "utils_keyval_lst.h"

struct s_hashtbl	g_envs = {};

static unsigned int	hash(const char *key)
{
	int				counter;
	unsigned int	val;
	unsigned int	tmp;

	counter = 0;
	val = 0;
	while (key[counter])
	{
		val += key[counter];
		tmp = val & 0xf0000000;
		if (tmp)
		{
			val = val ^ (tmp >> 24);
			val = val ^ tmp;
		}
		counter += 1;
	}
	return (val % TBLSIZE);
}

struct s_keyval	*hashtbl_lookup(const char *key)
{
	struct s_keyval	*tmp;

	tmp = g_envs.hashtbl[hash(key)];
	while (tmp)
	{
		if (ft_strcmp(key, tmp->key) == 0)
			return (tmp);
		tmp = tmp->next;
	}
	return (NULL);
}

void	insert_hashtbl(const char *key, const char *value)
{
	struct s_keyval	*tmp;
	int				h_bucket;

	h_bucket = hash(key);
	tmp = hashtbl_lookup(key);
	if (tmp)
	{
		free(tmp->val);
		tmp->val = ft_strdup(value);
	}
	else
	{
		keyval_add_back(&g_envs.hashtbl[h_bucket % TBLSIZE],
			new_node_of_bucket(ft_strdup(key), ft_strdup(value)));
		g_envs.size += 1;
	}
}

void	destroy_hashtbl(void)
{
	unsigned int	bucket;

	bucket = 0;
	while (bucket < TBLSIZE)
	{
		clear_bucket(&g_envs.hashtbl[bucket]);
		bucket += 1;
	}
}
