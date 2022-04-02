/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gvitor-s <gvitor-s@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/24 22:20:06 by gvitor-s          #+#    #+#             */
/*   Updated: 2021/08/30 14:06:54 by gvitor-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	len_n(int n);
static void		convert_n_str(char *p_str, int n, size_t len);

char	*ft_itoa(int n)
{
	int		n_tmp;
	char	*n_str;
	char	*p_str;
	size_t	len;

	n_tmp = n;
	len = len_n(n_tmp);
	n_str = (char *)malloc(sizeof(char) * (len + 1));
	if (!n_str)
		return (NULL);
	p_str = n_str;
	convert_n_str(p_str, n, len);
	return (n_str);
}

static size_t	len_n(int n_tmp)
{
	size_t	len;

	if (n_tmp <= 0)
		len = 1;
	else
		len = 0;
	while (n_tmp)
	{
		n_tmp /= 10;
		len++;
	}
	return (len);
}

static void	convert_n_str(char *p_str, int n, size_t len)
{
	size_t	tmp;
	size_t	power_of_10;

	if (n < 0)
	{
		tmp = (size_t)(-1) * n;
		len--;
		*p_str = '-';
		p_str++;
	}
	else
		tmp = n;
	power_of_10 = 1;
	while (len != 1)
	{
		power_of_10 *= 10;
		len--;
	}
	while (power_of_10)
	{
		*(p_str++) = ((tmp / power_of_10) % 10) + '0';
		power_of_10 /= 10;
	}
	*p_str = '\0';
}
