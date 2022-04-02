/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gvitor-s <gvitor-s@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/19 23:26:44 by gvitor-s          #+#    #+#             */
/*   Updated: 2021/08/30 14:08:53 by gvitor-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	int	is_in_set(char c, const char *set);

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*cpy_s1;
	size_t	counter;
	size_t	counter_f;

	if (s1 == NULL)
		return (NULL);
	else if (set == NULL)
	{
		cpy_s1 = ft_strdup(s1);
		return (cpy_s1);
	}
	counter = 0;
	while (s1[counter])
	{
		if (is_in_set(s1[counter], set))
			counter++;
		else if (!is_in_set(s1[counter], set))
			break ;
	}
	counter_f = ft_strlen(s1) - 1;
	while (is_in_set(s1[counter_f], set) && &s1[counter - 1] != &s1[counter_f])
		counter_f--;
	cpy_s1 = ft_substr(s1, counter, counter_f - counter + 1);
	return (cpy_s1);
}

static	int	is_in_set(char c, const char *set)
{
	size_t	counter;

	counter = -1;
	while (set[++counter])
	{
		if (c == set[counter])
			return (1);
	}
	return (0);
}
