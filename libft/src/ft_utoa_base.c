/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utoa_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gvitor-s <gvitor-s@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/09 18:10:36 by gvitor-s          #+#    #+#             */
/*   Updated: 2021/08/30 14:05:38 by gvitor-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

static size_t	len_of_n(size_t n, int len_base);
static size_t	power(size_t len_n, int len_base);
static void		convert_to_str(size_t n, char *base, char *result, size_t pw_b);

char	*ft_utoa_base(size_t n, char *base)
{
	char	*result;
	int		len_base;
	size_t	len_n;

	len_base = ft_strlen(base);
	if (len_base < 2)
		return (NULL);
	len_n = len_of_n(n, len_base);
	result = ft_calloc(len_n + 1, 1);
	if (!result)
		return (NULL);
	convert_to_str(n, base, result, power(len_n, len_base));
	return (result);
}

static size_t	len_of_n(size_t n, int len_base)
{
	size_t	len;

	if (n == 0)
		return (1);
	len = 0;
	while (n)
	{
		len++;
		n /= len_base;
	}
	return (len);
}

static void	convert_to_str(size_t n, char *base, char *result, size_t pw_b)
{
	int	len_base;

	len_base = ft_strlen(base);
	while (pw_b)
	{
		*(result++) = base[((n / pw_b) % len_base)];
		pw_b /= len_base;
	}
}

static size_t	power(size_t len_n, int len_base)
{
	size_t	pow;

	pow = 1;
	while (len_n > 1)
	{
		pow *= len_base;
		len_n--;
	}
	return (pow);
}
