/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gvitor-s <gvitor-s@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/11 12:16:45 by gvitor-s          #+#    #+#             */
/*   Updated: 2021/08/30 14:13:51 by gvitor-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	int	is_space(int c);

int	ft_atoi(const char *str)
{
	int	minus_signal;
	int	result;

	minus_signal = FALSE;
	while (is_space(*str))
		str++;
	if (*str == '-')
	{
		minus_signal = TRUE;
		str++;
	}
	else if (*str == '+')
		str++;
	result = 0;
	while (*str && ft_isdigit(*str))
	{
		result = result * 10 + (*str - '0');
		str++;
	}
	if (minus_signal)
		return (result * (-1));
	return (result);
}

static int	is_space(int c)
{
	if ((c >= '\t' && c <= '\r') || c == ' ')
		return (TRUE);
	return (FALSE);
}
