/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_striteri.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gvitor-s <gvitor-s@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/31 00:43:13 by gvitor-s          #+#    #+#             */
/*   Updated: 2021/12/31 00:43:13 by gvitor-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

void	ft_striteri(char *str, void (*f)(unsigned int, char *))
{
	int	index;

	index = 0;
	while (str[index] != '\0')
	{
		f(index, &str[index]);
		index += 1;
	}
}
