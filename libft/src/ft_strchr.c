/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gvitor-s <gvitor-s@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/19 12:45:48 by gvitor-s          #+#    #+#             */
/*   Updated: 2021/05/23 09:28:14 by gvitor-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *str, int c)
{
	size_t	counter;

	counter = 0;
	if (c == '\0')
		return ((char *)(str + ft_strlen(str)));
	while (str[counter])
	{
		if (str[counter] == (unsigned char) c)
			return ((char *)&str[counter]);
		counter++;
	}
	return (NULL);
}
