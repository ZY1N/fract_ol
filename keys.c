/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yinzhang <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/06 11:30:43 by yinzhang          #+#    #+#             */
/*   Updated: 2020/02/06 11:30:44 by yinzhang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	key_driver3(int key, void *pkg,
	void (*f)(void *mlx_ptr, void *win_ptr, t_mandel *mand, t_colors *palette))
{
	void		*mlx_ptr;
	void		*win_ptr;
	t_mandel	*mainmandel;

	mlx_ptr = ((t_package *)pkg)->mlx_ptr;
	win_ptr = ((t_package *)pkg)->win_ptr;
	mainmandel = ((t_package *)pkg)->mainmandel;
	if (key == ZOOM_IN)
	{
		mainmandel->realmin *= .9;
		mainmandel->realmax *= .9;
		mainmandel->imaginarymin *= .9;
		mainmandel->imaginarymax *= .9;
		mainmandel->zoomscale *= .9;
		(*f)(mlx_ptr, win_ptr, mainmandel, ((t_package *)pkg)->palette);
	}
	if (key == ZOOM_OUT)
	{
		mainmandel->realmin /= .9;
		mainmandel->realmax /= .9;
		mainmandel->imaginarymin /= .9;
		mainmandel->imaginarymax /= .9;
		mainmandel->zoomscale /= .9;
		(*f)(mlx_ptr, win_ptr, mainmandel, ((t_package *)pkg)->palette);
	}
}

void	key_driver2(int key, void *pkg,
	void (*f)(void *mlx_ptr, void *win_ptr, t_mandel *mand, t_colors *palette))
{
	void		*mlx_ptr;
	void		*win_ptr;
	t_mandel	*mainmandel;

	mlx_ptr = ((t_package *)pkg)->mlx_ptr;
	win_ptr = ((t_package *)pkg)->win_ptr;
	mainmandel = ((t_package *)pkg)->mainmandel;
	if (key == RIGHT)
	{
		mainmandel->realmin -= mainmandel->zoomscale * .25;
		mainmandel->realmax -= mainmandel->zoomscale * .25;
		(*f)(mlx_ptr, win_ptr, mainmandel, ((t_package *)pkg)->palette);
	}
	if (key == DOWN)
	{
		mainmandel->imaginarymin -= mainmandel->zoomscale * .25;
		mainmandel->imaginarymax -= mainmandel->zoomscale * .25;
		(*f)(mlx_ptr, win_ptr, mainmandel, ((t_package *)pkg)->palette);
	}
}

void	key_driver(int key, void *pkg,
	void (*f)(void *mlx_ptr, void *win_ptr, t_mandel *mand, t_colors *palette))
{
	void		*mlx_ptr;
	void		*win_ptr;
	t_mandel	*mainmandel;

	mlx_ptr = ((t_package *)pkg)->mlx_ptr;
	win_ptr = ((t_package *)pkg)->win_ptr;
	mainmandel = ((t_package *)pkg)->mainmandel;
	if (key == ESC)
		exit(1);
	if (key == LEFT)
	{
		mainmandel->realmin += (mainmandel->zoomscale * .25);
		mainmandel->realmax += (mainmandel->zoomscale * .25);
		(*f)(mlx_ptr, win_ptr, mainmandel, ((t_package *)pkg)->palette);
	}
	if (key == UP)
	{
		mainmandel->imaginarymin += mainmandel->zoomscale * .25;
		mainmandel->imaginarymax += mainmandel->zoomscale * .25;
		(*f)(mlx_ptr, win_ptr, mainmandel, ((t_package *)pkg)->palette);
	}
	key_driver2(key, pkg, f);
	key_driver3(key, pkg, f);
	key_driver4(key, pkg, f);
	key_driver5(key, pkg, f);
}

int		key_press(int key, void *pkg)
{
	t_mandel	*mainmandel;

	mainmandel = ((t_package *)pkg)->mainmandel;
	if (mainmandel->type == JULIA)
	{
		key_driver(key, pkg, julia_driver);
	}
	else if (mainmandel->type == MANDELBROT)
	{
		key_driver(key, pkg, mandelbrot_driver);
	}
	else if (mainmandel->type == BURNINGSHIP)
	{
		key_driver(key, pkg, bship_driver);
	}
	return (1);
}
