/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_command.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gvitor-s <gvitor-s>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/11 19:59:48 by gvitor-s          #+#    #+#             */
/*   Updated: 2022/03/11 20:14:27 by gvitor-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expand_str.h"

void	expand_command(struct s_tokens *head)
{
	while (head)
	{
		if (head->token == T_WORD)
		{
			expand_env_variables(&head->value);
			expand_quotes(&head->value);
		}
		head = head->next;
	}
}
