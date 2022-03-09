/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   err.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gvitor-s <gvitor-s@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/14 19:02:29 by gvitor-s          #+#    #+#             */
/*   Updated: 2022/03/09 14:57:40 by gvitor-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "tokenizer.h"
#include <errno.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include "hashtable.h"

int	raise_tokenizer_err(char const *msg, struct s_tokens **info)
{
	if (info != NULL && *info != NULL)
		clear_tokens(info);
	ft_putendl_fd((char *)msg, STDERR_FILENO);
	return (-1);
}

int	raise_env_error(void)
{
	destroy_hashtbl();
	ft_putendl_fd("Wrong allocation on environments variables\n",
		STDERR_FILENO);
	return (-1);
}
