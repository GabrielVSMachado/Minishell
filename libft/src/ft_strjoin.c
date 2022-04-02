/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gvitor-s <gvitor-s@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/19 20:04:44 by gvitor-s          #+#    #+#             */
/*   Updated: 2021/08/30 14:14:11 by gvitor-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(const char *s1, const char *s2)
{
	char	*final_str;
	int		counter;
	int		len_f_str;

	if (!s1 || !s2)
		return (NULL);
	len_f_str = (ft_strlen(s1) + ft_strlen(s2) + 1);
	final_str = (char *)malloc(sizeof(char) * len_f_str);
	if (final_str == NULL)
		return (NULL);
	counter = 0;
	while (*s1)
		final_str[counter++] = *(s1++);
	while (*s2)
		final_str[counter++] = *(s2++);
	final_str[counter] = '\0';
	return (final_str);
}
