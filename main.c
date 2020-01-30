/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yinzhang <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/27 08:28:19 by yinzhang          #+#    #+#             */
/*   Updated: 2020/01/27 12:08:38 by yinzhang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "minilibx_macos/mlx.h"

void	julia_driver()
{
	printf("greysama\n");
}

double mapToReal(int x, int imageWidth, double minR, double maxR)
{
	double range = maxR - minR;
	// [0, width]
	// [0, max-minR] - val * range / width
	// [inR, maxR]
	return(x * (range / imageWidth) + minR); 
}

double mapToImaginary(int x, int imageWidth, double minI, double maxI)
{
	double range = maxI - minI;
	// [0, width]
	// [0, max-minR] - val * range / width
	// [inR, maxR]
	return(x * (range / imageWidth) + minI); 
}

int findMandelbrot(double cr, double ci, int max_iterations)
{
	int i = 0;
	double zr = 0.0, zi = 0.0;
	while (i < max_iterations && zr *zr + zi * zi < 4)
	{
		double tmp = zr * zr - zi * zi + cr;
		zi = 2.0 * zr * zi + ci;
		zr = tmp;
		i++;
	}
	return(i);
}

void	mandelbrot_driver()
{
	int imageWidth, imageHeight, maxN;
	double minR, maxR, minI, maxI;
	void *mlx_ptr;
	void *win_ptr;

	mlx_ptr = mlx_init();
	win_ptr = mlx_new_window(mlx_ptr, 512, 512, "fractol beta");

	imageWidth = 512;
	imageHeight = 512;
	maxN = 255;
	minR = -1.5;
	maxR = 0.7;
	minI = -1.0;
	maxI = 1.0;

	for(int y = 0; y < imageHeight; y++)
	{
		for(int x = 0; x < imageWidth; x++)
		{
			double cr = mapToReal(x, imageWidth, minR, maxR);
			double ci = mapToImaginary(y, imageHeight, minI, maxI);
			int n = findMandelbrot(cr, ci, maxN);
			int r = (n % 256);
			int g = (n % 256);
			int b = (n % 256);
			int rgb;
			rgb = (r << 16 | g << 8 | b);
			mlx_pixel_put(mlx_ptr, win_ptr, x, y, rgb);
			printf("r%d g%d b%d\n", n% 256, n % 256, n % 256);
		}
	}
	mlx_loop(mlx_ptr);
}

int		ft_strcmp(char *s1, char *s2)
{
	int i;

	i = 0;
	while(s1[i] && s2[i] && s1[i] == s2[i])
		i++;
	return(s1[i] - s2[i]);
}

void	fractal_driver(char *s)
{
	if(!ft_strcmp(s, "julia") || !ft_strcmp(s, "Julia"))
		julia_driver();
	else if(!ft_strcmp(s, "mandelbrot") || !ft_strcmp(s, "Mandelbrot"))
		mandelbrot_driver();
}

int		main(int argc, char **argv)
{
	if(argc == 2)
	{
		fractal_driver(argv[1]);
	}
	else
		printf("Usage: ./fractol Julia Mandelbrot OneMore\n");
}
