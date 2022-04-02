/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gvitor-s <gvitor-s@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/18 18:37:48 by gvitor-s          #+#    #+#             */
/*   Updated: 2021/08/30 14:06:19 by gvitor-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h" 

void	*ft_memcpy(void *dst, const void *src, size_t buffer_size)
{
	size_t			count_d;
	size_t			count_s;
	unsigned char	*p_dst;
	unsigned char	*p_src;

	p_dst = (unsigned char *)dst;
	p_src = (unsigned char *)src;
	if (dst == NULL && src == NULL)
		return (NULL);
	count_d = 0;
	count_s = 0;
	while (buffer_size > count_d)
		(p_dst)[count_d++] = (p_src)[count_s++];
	return (dst);
}
