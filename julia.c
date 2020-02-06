/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   julia.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yinzhang <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/06 12:18:52 by yinzhang          #+#    #+#             */
/*   Updated: 2020/02/06 12:18:53 by yinzhang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int		findjulia(double a, double b, int max_iterations, mandel *mand)
{
	int		i;
	double	zr;
	double	zi;
	int		flag;
	double	tmp;

	tmp = 0;
	i = 0;
	flag = 0;
	zr = a * a - b * b;
	zi = 2 * a * b;
	while (i < max_iterations)
	{
		tmp = zr * zr - zi * zi + map_to_real(mand->xmouse, mand->imagewidth,
			mand->realMin, mand->realMax);
		zi = 2 * zr * zi + map_to_imaginary(mand->ymouse, mand->imageHeight,
			mand->imaginaryMin, mand->imaginaryMax);
		zr = tmp;
		if (zr * zr + zi * zi > 4)
			break ;
		i++;
	}
	return (i);
}

int		is_in_julia(mandel *mand, int x, int y)
{
	int		n;
	double	cr;
	double	ci;

	n = 0;
	cr = map_to_real(x, mand->imagewidth, mand->realMin, mand->realMax);
	ci = map_to_imaginary(y, mand->imageHeight, mand->imaginaryMin
		, mand->imaginaryMax);
	n = findjulia(cr, ci, mand->iterations, mand);
	return (n);
}

void	julia_driver(void *mlx_ptr, void *win_ptr, mandel *mand, colors *p)
{
	int n;
	int rgb;
	int x;
	int y;

	x = 0;
	y = 0;
	mlx_clear_window(mlx_ptr, win_ptr);
	while (y < mand->imageHeight)
	{
		x = 0;
		while (x < mand->imagewidth)
		{
			n = is_in_julia(mand, x, y);
			rgb = ((n + p->red) * mand->randseed % 256) << 16 |
				((n + p->green) * mand->randseed % 256) << 8
				| ((n + p->blue) * mand->randseed % 256);
			if (n < mand->iterations - 1)
				mlx_pixel_put(mlx_ptr, win_ptr, x, y, rgb);
			x++;
		}
		y++;
	}
}
