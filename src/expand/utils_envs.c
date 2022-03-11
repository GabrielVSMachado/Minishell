/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_envs.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gvitor-s <gvitor-s>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/09 14:23:03 by gvitor-s          #+#    #+#             */
/*   Updated: 2022/03/10 22:50:29 by gvitor-s         ###   ########.fr       */
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

unsigned int	len_env_name(char *env_name)
{
	char	*tmp;

	tmp = env_name;
	tmp += 1;
	if (ft_isdigit(*tmp) || *tmp == '?')
		return (1);
	while (*tmp && (ft_isalnum(*tmp) || *tmp == '_'))
		tmp += 1;
	return (tmp - (env_name + 1));
}

char	*treat_envs(char *env_name)
{
	unsigned int	len_name;
	struct s_keyval	*p_env;
	char			*tmp;

	tmp = env_name;
	len_name = len_env_name(env_name);
	tmp += 1;
	tmp = ft_memcpy(malloc(len_name + 1), tmp, len_name);
	tmp[len_name] = 0;
	p_env = hashtbl_lookup(tmp);
	free(tmp);
	if (NOT p_env)
		return (ft_strdup(""));
	return (ft_strdup(p_env->val));
}
