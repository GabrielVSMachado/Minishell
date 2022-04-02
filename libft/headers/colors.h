/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gvitor-s <gvitor-s@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/23 20:49:35 by gvitor-s          #+#    #+#             */
/*   Updated: 2021/12/23 20:49:35 by gvitor-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COLORS_H
# define COLORS_H

typedef struct s_hsv
{
	double	c;
	double	x;
	double	m;
	double	h_;
}	t_hsv;

typedef struct s_rgb
{
	double	r;
	double	g;
	double	b;
}	t_rgb;

int		ft_hsv_to_rgb(double h, double v, double s);
#endif
