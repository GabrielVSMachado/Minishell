/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_exec.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gvitor-s <gvitor-s>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/19 11:44:37 by gvitor-s          #+#    #+#             */
/*   Updated: 2022/03/19 13:04:29 by gvitor-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "linked_list.h"
#include "parsing.h"
#include <stddef.h>
#include <stdlib.h>

char *const	*gen_argv(t_list *params, char *name)
{
	char *const	*argv;
	char		**tmp;
	size_t		lenlst;

	lenlst = ft_lstsize(params);
	argv = malloc(sizeof(char *) * (lenlst + 2));
	tmp = (char **)argv;
	*tmp = name;
	tmp += 1;
	while (lenlst--)
	{
		*tmp = params->content;
		params = params->next;
		tmp += 1;
	}
	*tmp = NULL;
	return (argv);
}
