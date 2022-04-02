/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gvitor-s <gvitor-s@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/18 18:38:56 by gvitor-s          #+#    #+#             */
/*   Updated: 2021/08/30 14:06:05 by gvitor-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	set_for_multiple_of_8_or_4_bytes(void *s, unsigned long int c,
		unsigned long int *n)
{
	unsigned long int	len;
	unsigned long int	operation_size;
	void				*keep;

	operation_size = sizeof(unsigned long int);
	len = *n / operation_size;
	keep = s;
	while (len-- > 0)
	{
		((unsigned long int *) keep)[0] = c;
		keep += operation_size;
	}
	*n %= operation_size;
	return (keep - s);
}

static int	set_for_multiple_of_64_or_32_bytes(void *s, unsigned long int c,
		unsigned long int *n)
{
	unsigned long int	len;
	unsigned long int	operation_size;
	void				*keep;

	operation_size = sizeof(unsigned long int);
	keep = s;
	len = *n / (operation_size * 8);
	while (len-- > 0)
	{
		((unsigned long int *) keep)[0] = c;
		((unsigned long int *) keep)[1] = c;
		((unsigned long int *) keep)[2] = c;
		((unsigned long int *) keep)[3] = c;
		((unsigned long int *) keep)[4] = c;
		((unsigned long int *) keep)[5] = c;
		((unsigned long int *) keep)[6] = c;
		((unsigned long int *) keep)[7] = c;
		keep += (8 * operation_size);
	}
	*n %= (operation_size * 8);
	return (keep - s);
}

void	*ft_memset(void *s, int c, unsigned long int n)
{
	unsigned long int	operation_size;
	unsigned long int	long_ch_set;
	void				*l_s;

	l_s = s;
	operation_size = sizeof(unsigned long int);
	if (n >= 8)
	{
		long_ch_set = (unsigned char)c;
		long_ch_set |= long_ch_set << 8;
		long_ch_set |= long_ch_set << 16;
		if (operation_size > 4)
			long_ch_set |= (long_ch_set << 16) << 16;
		while ((long int)l_s % operation_size != 0 && n-- > 0)
			((t_byte *) l_s++)[0] = c;
		l_s += set_for_multiple_of_64_or_32_bytes(s, long_ch_set, &n);
		l_s += set_for_multiple_of_8_or_4_bytes(l_s, long_ch_set, &n);
	}
	while (n-- > 0)
		((t_byte *) l_s++)[0] = c;
	return (s);
}
