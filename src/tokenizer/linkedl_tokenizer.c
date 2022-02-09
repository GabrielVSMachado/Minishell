/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gvitor-s <gvitor-s@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/08 22:11:17 by gvitor-s          #+#    #+#             */
/*   Updated: 2022/02/08 22:11:17 by gvitor-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokenizer.h"

struct s_tokens	*new_token(char *content, unsigned int token)
{
	struct s_tokens	*node;

	node = malloc(sizeof(struct s_tokens));
	if (node == NULL)
	{
		return (NULL);
	}
	node->value = content;
	node->token = token;
	node->next = NULL;
	return (node);
}
