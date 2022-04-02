/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gvitor-s <gvitor-s@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/19 14:01:08 by gvitor-s          #+#    #+#             */
/*   Updated: 2021/08/30 14:02:17 by gvitor-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	len_li;

	len_li = ft_strlen(little);
	if (len_li == 0)
		return ((char *)big);
	while (*big && len != 0)
	{
		if (ft_strncmp(big, little, len_li) == 0 && len >= len_li)
			return ((char *)big);
		big++;
		len--;
	}
	return (NULL);
}
