/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mandelbrot.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yinzhang <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/06 12:18:58 by yinzhang          #+#    #+#             */
/*   Updated: 2020/02/06 12:18:59 by yinzhang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int findMandelbrot(double cr, double ci, int max_iterations)
{
	int i = 0;

	double zr = 0;
	double zi = 0;
	while (i < max_iterations && zr * zr + zi * zi < 4)
	{
		double tmp = zr * zr - zi * zi + cr;
		zi = 2 * zi * zr + ci;
		zr = tmp;
		i++;
	}
	return(i);
}

void	mandelbrot_driver(void *mlx_ptr, void *win_ptr, mandel *mand, colors *mainmandel)
{
	mlx_clear_window(mlx_ptr, win_ptr);
	int rando = mand->randseed;

	for(int y = 0 ;y < mand->imageHeight; y++)
	{
		for(int x = 0 ;x < mand->imagewidth; x++)
		{
			double cr = map_to_real(x, mand->imagewidth, mand->realMin, mand->realMax);
			double ci = map_to_imaginary(y, mand->imageHeight, mand->imaginaryMin, mand->imaginaryMax);
			int n = findMandelbrot(cr, ci, mand->iterations);
			int r = ((n + mainmandel->red) * rando % 256);
			int g = ((n + mainmandel->green) * rando % 256);
			int b = ((n + mainmandel->blue) * rando % 256);
			int rgb;
			rgb = (r << 16 | g << 8 | b);
			if (n < mand->iterations - 1)
				mlx_pixel_put(mlx_ptr, win_ptr, x, y, rgb);
		}
	}
}
