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

#include "fractol.h"

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
	while (i < max_iterations && zr * zr + zi * zi < 4)
	{
		double tmp = zr * zr - zi * zi + cr;
		zi = 2.0 * zr * zi + ci;
		zr = tmp;
		i++;
	}
	return(i);
}

void	mandelbrot_driver(void *mlx_ptr, void *win_ptr, mandel *mand, colors *palette)
{

	mlx_clear_window(mlx_ptr, win_ptr);
	int rando = rand();

	for(int y = 0; y < mand->imageHeight; y++)
	{
		for(int x = 0; x < mand->imageWidth; x++)
		{
			double cr = mapToReal(x, mand->imageWidth, mand->realMin, mand->realMax);
			double ci = mapToImaginary(y, mand->imageHeight, mand->imaginaryMin, mand->imaginaryMax);
			int n = findMandelbrot(cr, ci, mand->iterations);
			int r = ((n + palette->red) * rando % 256);
			int g = ((n + palette->green) * rando % 256);
			int b = ((n + palette->blue) * rando % 256);
			int rgb;
			rgb = (r << 16 | g << 8 | b);
			if (n < mand->iterations - 1)
				mlx_pixel_put(mlx_ptr, win_ptr, x, y, rgb);
			printf("%d\n", n);
			//printf("r%d g%d b%d\n", n% 256, n % 256, n % 256);
		}
	}
}

int		ft_strcmp(char *s1, char *s2)
{
	int i;

	i = 0;
	while(s1[i] && s2[i] && s1[i] == s2[i])
		i++;
	return(s1[i] - s2[i]);
}

int		key_press(int key, void *pkg)
{
	void *mlx_ptr;
	void *win_ptr;
	mandel *mainMandel;

	mlx_ptr = ((package *)pkg)->mlx_ptr;
	win_ptr = ((package *)pkg)->win_ptr;
	mainMandel = ((package *)pkg)->mainMandel;

	//printf("its working %d\n", key);
	if (key == 53) //escape
		exit(1);
	//for zoomies later on
	//if (key == 31) //o xkey
	//if (key == 35) //p kxey


	if (key == 12) //q
	{
		((package *)pkg)->palette->red += 5;
		mandelbrot_driver(mlx_ptr, win_ptr, mainMandel, ((package *)pkg)->palette);
	}
	if (key == 13) //w
	{
		((package *)pkg)->palette->green += 5;
		mandelbrot_driver(mlx_ptr, win_ptr, mainMandel, ((package *)pkg)->palette);
	}
	if (key == 14) //e
	{
		((package *)pkg)->palette->blue += 5;
		mandelbrot_driver(mlx_ptr, win_ptr, mainMandel, ((package *)pkg)->palette);
	}
	if (key == 0) //a
	{
		((package *)pkg)->palette->red -= 5;
		mandelbrot_driver(mlx_ptr, win_ptr, mainMandel, ((package *)pkg)->palette);
	}
	if (key == 1) //s
	{
		((package *)pkg)->palette->green -= 5;
		mandelbrot_driver(mlx_ptr, win_ptr, mainMandel, ((package *)pkg)->palette);
	}	
	if (key == 2) //d
	{
		((package *)pkg)->palette->blue -= 5;
		mandelbrot_driver(mlx_ptr, win_ptr, mainMandel, ((package *)pkg)->palette);
	}
	return (1);
}

int		mouse_move(int x, int y)
{
	//printf("x: %d y: %d\n", x, y);
	return (1);
}



void	julia_driver(void *mlx_ptr, void *win_ptr, mandel *mand, colors *palette)
{
	mlx_clear_window(mlx_ptr, win_ptr);
	int rando = rand();

	for(int y = 0; y < mand->imageHeight; y++)
	{
		for(int x = 0; x < mand->imageWidth; x++)
		{
			double cr = mapToReal(x, mand->imageWidth, mand->realMin, mand->realMax);
			double ci = mapToImaginary(y, mand->imageHeight, mand->imaginaryMin, mand->imaginaryMax);
			int n = findMandelbrot(cr, ci, mand->iterations);
			int r = ((n + palette->red) * rando % 256);
			int g = ((n + palette->green) * rando % 256);
			int b = ((n + palette->blue) * rando % 256);
			int rgb;
			rgb = (r << 16 | g << 8 | b);
			if (n < mand->iterations - 1)
				mlx_pixel_put(mlx_ptr, win_ptr, x, y, rgb);
		}
	}
}

mandel *mainMandelInit()
{
	mandel *ret;

	ret = malloc(sizeof(mandel));
	ret->imageWidth = 900;
	ret->imageHeight = 900;
	ret->iterations = 256;
	ret->realMin = -2;
	ret->realMax = 2;
	ret->imaginaryMin = -2;
	ret->imaginaryMax = 2;
	return(ret);
}

void	fractal_driver(char *s)
{
	void *mlx_ptr;
	void *win_ptr;
	mandel *mainMandel;
	colors *palette;
	package pkg;

	palette = malloc(sizeof(colors));

	palette->red = 0;
	palette->green = 0;
	palette->blue = 0;

	mainMandel = mainMandelInit();
	mlx_ptr = mlx_init();
	win_ptr = mlx_new_window(mlx_ptr, 900, 900, "fractol beta");
	pkg.mlx_ptr = mlx_ptr;
	pkg.win_ptr = win_ptr;
	pkg.mainMandel = mainMandel;
	pkg.palette = palette;

	if(!ft_strcmp(s, "julia") || !ft_strcmp(s, "Julia"))
	{
		mlx_key_hook(win_ptr, &key_press, &pkg);
		mlx_hook(win_ptr, 6, 0, &mouse_move, s);
		julia_driver(mlx_ptr, win_ptr, mainMandel, palette);
		mlx_loop(mlx_ptr);
	}
	else if(!ft_strcmp(s, "mandelbrot") || !ft_strcmp(s, "Mandelbrot"))
	{
		mandelbrot_driver(mlx_ptr, win_ptr, mainMandel, palette);
		mlx_key_hook(win_ptr, &key_press, &pkg);
		mlx_hook(win_ptr, 6, 0, &mouse_move, NULL);
		mlx_loop(mlx_ptr);
	}
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
