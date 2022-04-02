/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_hsv_to_rgb.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gvitor-s <gvitor-s@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/11 11:22:19 by gvitor-s          #+#    #+#             */
/*   Updated: 2022/04/02 14:12:46 by gvitor-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int		rgb_format(t_rgb *rgb);
static double	fabs(double n);

int	ft_hsv_to_rgb(double h, double v, double s)
{
	t_hsv	conv;
	t_rgb	rgb;

	rgb = (t_rgb){};
	conv.c = v * s;
	conv.h_ = h / 60;
	conv.x = conv.c * (1 - fabs(((int)conv.h_ % 2) - 1
				+ (conv.h_ - (int)conv.h_)));
	if (0 <= conv.h_ && 1 >= conv.h_)
		rgb = (t_rgb){.r = conv.c, .g = conv.x, .b = 0};
	else if (1 < conv.h_ && 2 >= conv.h_)
		rgb = (t_rgb){.r = conv.x, .g = conv.c, .b = 0};
	else if (2 < conv.h_ && 3 >= conv.h_)
		rgb = (t_rgb){.r = 0, .g = conv.c, .b = conv.x};
	else if (3 < conv.h_ && 4 >= conv.h_)
		rgb = (t_rgb){.r = 0, .g = conv.x, .b = conv.c};
	else if (4 < conv.h_ && 5 >= conv.h_)
		rgb = (t_rgb){.r = conv.x, .g = 0, .b = conv.c};
	else if (5 < conv.h_ && 6 >= conv.h_)
		rgb = (t_rgb){.r = conv.c, .g = 0, .b = conv.x};
	conv.m = v - conv.c;
	rgb.r += conv.m;
	rgb.g += conv.m;
	rgb.b += conv.m;
	return (rgb_format(&rgb));
}

static int	rgb_format(t_rgb *rgb)
{
	int	r;
	int	g;
	int	b;

	r = (int)(rgb->r * 255);
	g = (int)(rgb->g * 255);
	b = (int)(rgb->b * 255);
	return (((r & 0xFF) << 16) + ((g & 0xFF) << 8) + ((b & 0xFF) << 0));
}

static double	fabs(double n)
{
	if (n >= 0)
		return (n);
	return (-n);
}
