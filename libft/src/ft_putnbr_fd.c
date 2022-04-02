/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gvitor-s <gvitor-s@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/27 11:21:00 by gvitor-s          #+#    #+#             */
/*   Updated: 2021/08/30 14:10:19 by gvitor-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	put_n_tmp(size_t n_tmp, int fd);

void	ft_putnbr_fd(int n, int fd)
{
	size_t	n_tmp;

	if (n < 0)
	{
		n_tmp = (size_t)(-1) * n;
		ft_putchar_fd('-', fd);
	}
	else
		n_tmp = n;
	put_n_tmp(n_tmp, fd);
}

void	put_n_tmp(size_t n_tmp, int fd)
{
	if (n_tmp >= 10)
	{
		put_n_tmp (n_tmp / 10, fd);
		put_n_tmp (n_tmp % 10, fd);
	}
	else
		ft_putchar_fd(n_tmp + '0', fd);
}
