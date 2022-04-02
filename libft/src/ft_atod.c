/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atod.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gvitor-s <gvitor-s@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/11 21:10:40 by gvitor-s          #+#    #+#             */
/*   Updated: 2021/08/30 14:09:29 by gvitor-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static unsigned int	multiply_by_10(unsigned int *z);
static double		make_result(char *str);

double	ft_atod(const char *str)
{
	int		sign;

	sign = 1;
	while (*str == ' ')
		str++;
	if (*str == '+' || *str == '-')
	{
		sign = (*str == '+') + (*str == '-') * (-1);
		str++;
	}
	return (sign * (make_result((char *)str)));
}

static double	make_result(char *str)
{
	unsigned int		mantissa;
	unsigned int		exponent;
	unsigned int		power;

	mantissa = 0;
	while ('0' <= *str && *str <= '9')
	{
		mantissa = multiply_by_10(&mantissa) + (*str - '0');
		str++;
	}
	exponent = 1;
	if (*str == '.')
	{
		while (++str && ('0' <= *str && *str <= '9'))
		{
			mantissa = multiply_by_10(&mantissa) + (*str - '0');
			exponent++;
		}
	}
	power = 1;
	while (--exponent)
		power = multiply_by_10(&power);
	return ((double)mantissa / (double)power);
}

static unsigned int	multiply_by_10(unsigned int *z)
{
	return ((*z << 2 << 1) + (*z << 1));
}
