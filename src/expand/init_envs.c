/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_envs.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gvitor-s <gvitor-s>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/09 14:23:03 by gvitor-s          #+#    #+#             */
/*   Updated: 2022/03/09 19:23:25 by gvitor-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hashtable.h"
#include "libft.h"
#include "error.h"

extern char				**environ;
extern struct s_hashtbl	g_envs;

int	init_envs(void)
{
	char			**tmp;
	char			*p_equal;
	unsigned int	len_key;
	char			*key;

	tmp = environ;
	while (*tmp)
	{
		p_equal = ft_strchr(*tmp, '=');
		len_key = p_equal - *tmp;
		key = ft_memcpy(malloc(len_key + 1), *tmp, len_key);
		if (NOT key)
			return (raise_env_error());
		key[len_key] = 0;
		insert_hashtbl(key, ft_strdup(p_equal + 1));
		tmp += 1;
	}
	return (0);
}
