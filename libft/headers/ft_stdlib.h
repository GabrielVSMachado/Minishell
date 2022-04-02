/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_stdlib.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gvitor-s <gvitor-s@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/23 21:09:10 by gvitor-s          #+#    #+#             */
/*   Updated: 2021/12/23 21:09:10 by gvitor-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_STDLIB_H
# define FT_STDLIB_H

# include <stdlib.h>

int		ft_atoi(const char *str);
int		ft_abs(int n);

double	ft_atod(const char *str);

void	*ft_calloc(size_t type, size_t size);

char	*ft_itoa(int n);
char	*ft_utoa_base(size_t n, char *base);
#endif
