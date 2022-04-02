/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gvitor-s <gvitor-s>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/12 20:37:16 by gvitor-s          #+#    #+#             */
/*   Updated: 2022/04/02 02:36:15 by gvitor-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hashtable.h"
#include "libft.h"

extern struct s_hashtbl	g_envs;

void	env(void)
{
	unsigned int	bucket;
	struct s_keyval	*current_node;

	bucket = 0;
	while (bucket < TBLSIZE)
	{
		current_node = g_envs.hashtbl[bucket];
		while (current_node)
		{
			if (ft_strcmp(current_node->key, "?") && current_node->next)
			{
				current_node = current_node->next;
				continue ;
			}
			else
				break ;
			ft_putstr_fd(current_node->key, STDOUT_FILENO);
			ft_putchar_fd('=', STDOUT_FILENO);
			ft_putendl_fd(current_node->val, STDOUT_FILENO);
			current_node = current_node->next;
		}
		bucket += 1;
	}
}
