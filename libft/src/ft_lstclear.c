/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gvitor-s <gvitor-s@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/29 16:58:11 by gvitor-s          #+#    #+#             */
/*   Updated: 2021/05/30 16:42:59 by gvitor-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*p_tmp;

	if (!lst)
		return ;
	while (*lst)
	{
		p_tmp = (*lst)->next;
		ft_lstdelone(*lst, del);
		*lst = p_tmp;
	}
}
