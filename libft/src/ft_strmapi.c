/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gvitor-s <gvitor-s@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/26 16:29:37 by gvitor-s          #+#    #+#             */
/*   Updated: 2021/05/28 15:56:20 by gvitor-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char			*str_final;
	unsigned int	counter;

	counter = -1;
	if (s == NULL)
		return (NULL);
	str_final = (char *)malloc(sizeof(char) * (ft_strlen(s) + 1));
	if (!str_final)
		return (NULL);
	while (s[++counter])
		*(str_final + counter) = (*f)(counter, s[counter]);
	*(str_final + counter) = '\0';
	return (str_final);
}
