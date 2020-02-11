/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yinzhang <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/06 14:56:28 by yinzhang          #+#    #+#             */
/*   Updated: 2020/02/06 14:56:29 by yinzhang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void		fill_colors(t_colors **palette)
{
	*palette = malloc(sizeof(t_mandel));
	(*palette)->red = 0;
	(*palette)->green = 0;
	(*palette)->blue = 0;
}

t_package	fill_pkg(t_mandel *mainmandel, t_colors *p,
	void *mlx_ptr, void *win_ptr)
{
	t_package pkg;

	pkg.mlx_ptr = mlx_ptr;
	pkg.win_ptr = win_ptr;
	pkg.mainmandel = mainmandel;
	pkg.palette = p;
	return (pkg);
}

void		free_things(t_mandel *mainmandel, t_colors *p,
	void *mlx_ptr, void *win_ptr)
{
	free(mainmandel);
	free(p);
	free(win_ptr);
	free(mlx_ptr);
}

void		init_mlx_win(void **mlx_ptr, void **win_ptr)
{
	*mlx_ptr = mlx_init();
	*win_ptr = mlx_new_window(*mlx_ptr, 750, 750, "fractol beta");
}

void		go_to_driver(t_mandel *mmandel, void *mlx_ptr,
	void *win_ptr, t_colors *p)
{
	if (mmandel->type == JULIA)
		julia_driver(mlx_ptr, win_ptr, mmandel, p);
	else if (mmandel->type == MANDELBROT)
		mandelbrot_driver(mlx_ptr, win_ptr, mmandel, p);
	else if (mmandel->type == BURNINGSHIP)
		bship_driver(mlx_ptr, win_ptr, mmandel, p);
	else
	{
		write(1, "Not Valid\n", 10);
		exit(1);
	}
}
