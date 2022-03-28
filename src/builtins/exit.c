/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gvitor-s <gvitor-s>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/27 19:47:37 by gvitor-s          #+#    #+#             */
/*   Updated: 2022/03/28 19:47:13 by gvitor-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hashtable.h"
#include "parsing.h"
#include <stdlib.h>

void	__exit(struct s_program **program)
{
	destroy_hashtbl();
	if (program)
		destroy_programs(program);
	exit(EXIT_SUCCESS);
}
