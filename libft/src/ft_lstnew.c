/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gvitor-s <gvitor-s@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/29 11:53:04 by gvitor-s          #+#    #+#             */
/*   Updated: 2021/05/30 14:56:15 by gvitor-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(void *content)
{
	t_list	*created;

	created = (t_list *)malloc(sizeof(t_list));
	if (!created)
		return (NULL);
	created->content = content;
	created->next = NULL;
	return (created);
}
