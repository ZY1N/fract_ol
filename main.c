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

int		mouse_move(int x, int y, t_package *pkg)
{
	t_mandel	*mainmandel;
	void		*mlx_ptr;
	void		*win_ptr;

	mainmandel = pkg->mainmandel;
	mlx_ptr = ((t_package *)pkg)->mlx_ptr;
	win_ptr = ((t_package *)pkg)->win_ptr;
	mainmandel->xmouse = x;
	mainmandel->ymouse = y;
	julia_driver(mlx_ptr, win_ptr, mainmandel, ((t_package *)pkg)->palette);
	return (1);
}

void	fractal_driver(char *s)
{
	void		*mlx_ptr;
	void		*win_ptr;
	t_mandel	*mainmandel;
	t_colors	*palette;
	t_package	pkg;

	fill_colors(&palette);
	mainmandel = main_mandel_init();
	init_mlx_win(&mlx_ptr, &win_ptr);
	pkg = fill_pkg(mainmandel, palette, mlx_ptr, win_ptr);
	if (!ft_strcmp(s, "julia") || !ft_strcmp(s, "Julia"))
	{
		mainmandel->type = JULIA;
		mlx_hook(win_ptr, 6, 0, &mouse_move, &pkg);
	}
	else if (!ft_strcmp(s, "mandelbrot") || !ft_strcmp(s, "Mandelbrot"))
		mainmandel->type = MANDELBROT;
	else if (!ft_strcmp(s, "burning ship") || !ft_strcmp(s, "Burning Ship"))
		mainmandel->type = BURNINGSHIP;
	go_to_driver(mainmandel, mlx_ptr, win_ptr, palette);
	mlx_key_hook(win_ptr, &key_press, &pkg);
	mlx_loop(mlx_ptr);
	free_things(mainmandel, palette, mlx_ptr, win_ptr);
}

int		main(int argc, char **argv)
{
	if (argc == 2)
	{
		fractal_driver(argv[1]);
	}
	else
		write(1, "Usage: ./fractol Julia Mandelbrot OneMore\n", );
}
