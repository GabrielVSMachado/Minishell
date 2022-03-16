/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_parsing.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gvitor-s <gvitor-s>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/16 16:29:49 by gvitor-s          #+#    #+#             */
/*   Updated: 2022/03/16 16:31:39 by gvitor-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

struct s_io	*new_io(char *content, unsigned int type)
{
	struct s_io	*result;

	result = (struct s_io *)malloc(sizeof(struct s_io));
	if (NOT result)
		return (NULL);
	result->type = type;
	result->file = content;
	return (result);
}
