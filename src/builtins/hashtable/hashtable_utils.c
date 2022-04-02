/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hashtable_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gvitor-s <gvitor-s>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/12 17:14:04 by gvitor-s          #+#    #+#             */
/*   Updated: 2022/04/02 02:40:14 by gvitor-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_stdlib.h"
#include "ft_string.h"
#include "hashtable.h"
#include "libft.h"
#include <stdlib.h>
#include "expand/envs.h"

extern struct s_hashtbl	g_envs;

static struct s_keyval	**create_hashtbl(void)
{
	struct s_keyval	**result;

	result = (struct s_keyval **)ft_calloc(sizeof(struct s_keyval *), TBLSIZE);
	if (NOT (result))
		return (NULL);
	return (result);
}

int	init_hashtbl(void)
{
	g_envs.hashtbl = create_hashtbl();
	if (NOT (g_envs.hashtbl))
		return (-1);
	g_envs.size = 0;
	return (init_envs());
}

void	insert_ext_code(int ext_code)
{
	if (hashtbl_lookup("?"))
		insert_hashtbl("?", ft_itoa(ext_code));
	else
		insert_hashtbl(ft_strdup("?"), ft_itoa(ext_code));
}
