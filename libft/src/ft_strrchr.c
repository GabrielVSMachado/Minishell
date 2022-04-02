/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gvitor-s <gvitor-s@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/19 13:43:37 by gvitor-s          #+#    #+#             */
/*   Updated: 2021/05/23 10:53:28 by gvitor-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *str, int c)
{
	int	counter;

	counter = 0;
	if ((unsigned char)c == '\0')
		return ((char *)(str + ft_strlen(str)));
	while (str[counter])
		counter++;
	counter--;
	while (counter >= 0)
	{
		if (str[counter] == (unsigned char)c)
			return ((char *)(str + counter));
		counter--;
	}
	return (NULL);
}
