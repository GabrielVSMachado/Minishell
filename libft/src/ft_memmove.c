/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gvitor-s <gvitor-s@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/18 17:43:30 by gvitor-s          #+#    #+#             */
/*   Updated: 2021/08/30 14:06:12 by gvitor-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h" 

void	*ft_memmove(void *dst, const void *src, size_t n)
{
	char	*c_src;
	char	*c_dst;

	if (dst == NULL && src == NULL)
		return (NULL);
	c_src = (char *)src;
	c_dst = (char *)dst;
	if (src > dst)
	{
		while (n-- != 0)
			*(c_dst++) = *(c_src++);
	}
	else
	{
		while (n-- != 0)
			c_dst[n] = c_src[n];
	}
	return (dst);
}
