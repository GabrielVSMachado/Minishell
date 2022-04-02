/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gvitor-s <gvitor-s@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/19 16:18:29 by gvitor-s          #+#    #+#             */
/*   Updated: 2021/08/30 14:08:40 by gvitor-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

static unsigned int	number_to_alloc(size_t len_str, size_t start,
		size_t max_len)
{
	if (len_str < start)
		return (0);
	else if (len_str - start > max_len)
		return (max_len);
	return (len_str - start);
}

char	*ft_substr(const char *str, size_t start, size_t max_len)
{
	char			*substr;
	size_t			counter;
	unsigned int	n_to_alloc;
	size_t			len_str;

	len_str = ft_strlen(str);
	n_to_alloc = number_to_alloc(len_str, start, max_len);
	substr = (char *)malloc(sizeof(char) * (n_to_alloc + 1));
	if (substr == NULL)
		return (NULL);
	counter = 0;
	if (len_str > start)
	{
		while (counter < n_to_alloc)
		{
			substr[counter] = str[start + counter];
			counter += 1;
		}
	}
	substr[counter] = '\0';
	return (substr);
}
