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



int		findJulia(double a, double b, int max_iterations, mandel *mand)
{
	int i = 0;

	double zr = 0.0;
	double zi = 0.0;
	int flag = 0;

	zr = a * a - b * b;
	zi = 2 * a * b;
	while(i < max_iterations)
	{
		double tmp = zr * zr - zi * zi + map_to_real(mand->xmouse, mand->imagewidth, mand->realMin, mand->realMax);
		zi = 2 * zr * zi + map_to_imaginary(mand->ymouse, mand->imageHeight, mand->imaginaryMin, mand->imaginaryMax);
		zr = tmp;	
		if (zr*zr + zi*zi > 4)
			break ;
		i++;
	}
	return(i);
}

void	julia_driver(void *mlx_ptr, void *win_ptr, mandel *mand, colors *mainmandel)
{
	mlx_clear_window(mlx_ptr, win_ptr);
	
	int rando = mand->randseed;
	for(int y = 0; y < mand->imageHeight; y++)
	{
		for(int x = 0; x < mand->imagewidth; x++)
		{
			double cr = map_to_real(x, mand->imagewidth, mand->realMin, mand->realMax);
			double ci = map_to_imaginary(y, mand->imageHeight, mand->imaginaryMin, mand->imaginaryMax);
			int n = findJulia(cr, ci, mand->iterations, mand);
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



int findBurningShip(double cr, double ci, int max_iterations)
{
	int i = 0;

	double zr = 0;
	double zi = 0;
	while (i < max_iterations && zr * zr + zi * zi < 4)
	{
		double tmp = zr * zr - zi * zi + cr;
		zi = fabs(2 * zi * zr + ci);
		zr = tmp;
		i++;
	}
	return(i);
}

void	burningship_driver(void *mlx_ptr, void *win_ptr, mandel *mand, colors *mainmandel)
{

	mlx_clear_window(mlx_ptr, win_ptr);
	int rando = mand->randseed;//rand();

	for(int y = 0 ;y < mand->imageHeight; y++)
	{
		for(int x = 0 ;x < mand->imagewidth; x++)
		{
			double cr = map_to_real(x, mand->imagewidth, mand->realMin, mand->realMax);
			double ci = map_to_imaginary(y, mand->imageHeight, mand->imaginaryMin, mand->imaginaryMax);
			int n = findBurningShip(cr, ci, mand->iterations);
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

int		mouse_move(int x, int y, package *pkg)
{
	mandel *mainmandel = pkg->mainmandel;
	void *mlx_ptr;
	void *win_ptr;

	mlx_ptr = ((package *)pkg)->mlx_ptr;
	win_ptr = ((package *)pkg)->win_ptr;
	mainmandel->xmouse = x;
	mainmandel->ymouse = y;
	julia_driver(mlx_ptr, win_ptr, mainmandel, ((package *)pkg)->palette);
	return (1);
}



void	fractal_driver(char *s)
{
	void *mlx_ptr;
	void *win_ptr;
	mandel *mainmandel;
	colors *palatte;
	package pkg;

	mainmandel = malloc(sizeof(colors));

	palatte->red = 0;
	palatte->green = 0;
	palatte->blue = 0;

	mainmandel = main_mandel_init();
	mlx_ptr = mlx_init();
	win_ptr = mlx_new_window(mlx_ptr, 750, 750, "fractol beta");
	pkg.mlx_ptr = mlx_ptr;
	pkg.win_ptr = win_ptr;
	pkg.mainmandel = mainmandel;
	pkg.mainmandel = mainmandel;

	if(!ft_strcmp(s, "julia") || !ft_strcmp(s, "Julia"))
	{
		mainmandel->type = JULIA;
		mlx_key_hook(win_ptr, &key_press, &pkg);
		mlx_hook(win_ptr, 6, 0, &mouse_move, &pkg);
		julia_driver(mlx_ptr, win_ptr, mainmandel, palatte);
		mlx_loop(mlx_ptr);
	}
	else if(!ft_strcmp(s, "mandelbrot") || !ft_strcmp(s, "Mandelbrot"))
	{
		mainmandel->type = MANDELBROT; 
		mandelbrot_driver(mlx_ptr, win_ptr, mainmandel, palatte);
		mlx_key_hook(win_ptr, &key_press, &pkg);
		mlx_loop(mlx_ptr);
	}
	else if(!ft_strcmp(s, "burning ship") || !ft_strcmp(s, "Buring Ship"))
	{
		mainmandel->type = BURNINGSHIP;
		burningship_driver(mlx_ptr, win_ptr, mainmandel, palatte);
		mlx_key_hook(win_ptr, &key_press, &pkg);
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
