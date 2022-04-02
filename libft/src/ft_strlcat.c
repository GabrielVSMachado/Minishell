/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gvitor-s <gvitor-s@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/18 18:39:10 by gvitor-s          #+#    #+#             */
/*   Updated: 2021/05/28 15:26:17 by gvitor-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t len_dst_final)
{
	int			counter;
	char		*src_tmp;
	size_t		len_dst;

	src_tmp = (char *)src;
	len_dst = ft_strlen(dst);
	counter = 0;
	if (len_dst_final <= len_dst)
		return (ft_strlen(src) + len_dst_final);
	len_dst_final -= len_dst;
	while (*src_tmp && len_dst_final-- != 1)
		dst[len_dst + counter++] = *(src_tmp++);
	dst[counter + len_dst] = '\0';
	return (ft_strlen(src) + len_dst);
}
