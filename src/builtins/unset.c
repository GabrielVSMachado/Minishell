/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gvitor-s <gvitor-s>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/11 20:52:04 by gvitor-s          #+#    #+#             */
/*   Updated: 2022/04/01 14:50:13 by gvitor-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hashtable.h"
#include "libft.h"
#include "linked_list.h"

void	unset(struct s_list *params)
{
	struct s_keyval	*env;

	while (params)
	{
		env = remove_key(params->content);
		if (NOT env)
		{
			params = params->next;
			continue ;
		}
		free(env->key);
		free(env->val);
		free(env);
		env = NULL;
		params = params->next;
	}
}
