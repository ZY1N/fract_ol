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
	colors *palette;
	package pkg;

	mainmandel = malloc(sizeof(colors));

	palette->red = 0;
	palette->green = 0;
	palette->blue = 0;

	mainmandel = main_mandel_init();
	mlx_ptr = mlx_init();
	win_ptr = mlx_new_window(mlx_ptr, 750, 750, "fractol beta");
	pkg.mlx_ptr = mlx_ptr;
	pkg.win_ptr = win_ptr;
	pkg.mainmandel = mainmandel;
	pkg.palette = palette;

	if(!ft_strcmp(s, "julia") || !ft_strcmp(s, "Julia"))
	{
		mainmandel->type = JULIA;
		mlx_key_hook(win_ptr, &key_press, &pkg);
		mlx_hook(win_ptr, 6, 0, &mouse_move, &pkg);
		julia_driver(mlx_ptr, win_ptr, mainmandel, palette);
		mlx_loop(mlx_ptr);
	}
	else if(!ft_strcmp(s, "mandelbrot") || !ft_strcmp(s, "Mandelbrot"))
	{
		mainmandel->type = MANDELBROT; 
		mandelbrot_driver(mlx_ptr, win_ptr, mainmandel, palette);
		mlx_key_hook(win_ptr, &key_press, &pkg);
		mlx_loop(mlx_ptr);
	}
	else if(!ft_strcmp(s, "burning ship") || !ft_strcmp(s, "Buring Ship"))
	{
		mainmandel->type = BURNINGSHIP;
		burningship_driver(mlx_ptr, win_ptr, mainmandel, palette);
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
