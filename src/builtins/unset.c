/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gvitor-s <gvitor-s>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/11 20:52:04 by gvitor-s          #+#    #+#             */
/*   Updated: 2022/03/12 19:48:46 by gvitor-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hashtable.h"
#include "libft.h"

void	unset(const char	*key)
{
	struct s_keyval	*env;

	env = remove_key(key);
	if (NOT env)
		return ;
	free(env->key);
	free(env->val);
	free(env);
	env = NULL;
}
