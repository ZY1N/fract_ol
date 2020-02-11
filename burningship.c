/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   burningship.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yinzhang <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/06 12:19:03 by yinzhang          #+#    #+#             */
/*   Updated: 2020/02/06 12:19:04 by yinzhang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int		findburningship(double cr, double ci, int max_iterations)
{
	int		i;
	double	zr;
	double	zi;
	double	tmp;

	i = 0;
	zr = 0;
	zi = 0;
	tmp = 0;
	while (i < max_iterations && zr * zr + zi * zi < 4)
	{
		tmp = zr * zr - zi * zi + cr;
		zi = fabs(2 * zi * zr + ci);
		zr = tmp;
		i++;
	}
	return (i);
}

int		is_in_ship(mandel *mand, int x, int y)
{
	int		n;
	double	cr;
	double	ci;

	n = 0;
	cr = map_to_real(x, mand->imagewidth, mand->realMin, mand->realMax);
	ci = map_to_imaginary(y, mand->imageHeight, mand->imaginaryMin
		, mand->imaginaryMax);
	n = findburningship(cr, ci, mand->iterations);
	return (n);
}

void	bship_driver(void *mlx_ptr, void *win_ptr, mandel *mand, colors *p)
{
	int n;
	int rgb;
	int x;
	int y;

	x = 0;
	y = 0;
	n = 0;
	mlx_clear_window(mlx_ptr, win_ptr);
	while (y < mand->imageHeight)
	{
		x = 0;
		while (x < mand->imagewidth)
		{
			n = is_in_ship(mand, x, y);
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
