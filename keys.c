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

void	key_driver(int key, void *pkg, void (*f)(void *mlx_ptr, void *win_ptr, mandel *mand, colors *palette))
{
	void	*mlx_ptr;
	void	*win_ptr;
	mandel	*mainmandel;
	int		scale;

	mlx_ptr = ((package *)pkg)->mlx_ptr;
	win_ptr = ((package *)pkg)->win_ptr;
	mainmandel = ((package *)pkg)->mainmandel;
	scale = (mainmandel->realMax - mainmandel->realMin);
	if (key == ESC)
		exit(1);
	if (key == LEFT)
	{
		mainmandel->realMin += (mainmandel->zoomscale * .25);
		mainmandel->realMax += (mainmandel->zoomscale * .25);
		(*f)(mlx_ptr, win_ptr, mainmandel, ((package *)pkg)->palette);
	}
	if (key == UP)
	{
		mainmandel->imaginaryMin += mainmandel->zoomscale * .25;
		mainmandel->imaginaryMax += mainmandel->zoomscale * .25;
		(*f)(mlx_ptr, win_ptr, mainmandel, ((package *)pkg)->palette);
	}
	if (key == RIGHT)
	{
		mainmandel->realMin -= mainmandel->zoomscale * .25;
		mainmandel->realMax -= mainmandel->zoomscale * .25;
		(*f)(mlx_ptr, win_ptr, mainmandel, ((package *)pkg)->palette);
	}
	if (key == DOWN)
	{
		mainmandel->imaginaryMin -= mainmandel->zoomscale * .25;
		mainmandel->imaginaryMax -= mainmandel->zoomscale * .25;
		(*f)(mlx_ptr, win_ptr, mainmandel, ((package *)pkg)->palette);
	}
	if (key == ZOOM_IN)
	{
		mainmandel->realMin *= .9;
		mainmandel->realMax *= .9;
		mainmandel->imaginaryMin *= .9;
		mainmandel->imaginaryMax *= .9;
		mainmandel->zoomscale *= .9;
		(*f)(mlx_ptr, win_ptr, mainmandel, ((package *)pkg)->palette);
	}
	if (key == ZOOM_OUT)
	{
		mainmandel->realMin /= .9;
		mainmandel->realMax /= .9;
		mainmandel->imaginaryMin /= .9;
		mainmandel->imaginaryMax /= .9;
		mainmandel->zoomscale /= .9;
		(*f)(mlx_ptr, win_ptr, mainmandel, ((package *)pkg)->palette);
	}
	if (key == Q)
	{
		((package *)pkg)->palette->red += 5;
		(*f)(mlx_ptr, win_ptr, mainmandel, ((package *)pkg)->palette);
	}
	if (key == W)
	{
		((package *)pkg)->palette->green += 5;
		(*f)(mlx_ptr, win_ptr, mainmandel, ((package *)pkg)->palette);
	}
	if (key == E)
	{
		((package *)pkg)->palette->blue += 5;
		(*f)(mlx_ptr, win_ptr, mainmandel, ((package *)pkg)->palette);
	}
	if (key == A)
	{
		((package *)pkg)->palette->red -= 5;
		(*f)(mlx_ptr, win_ptr, mainmandel, ((package *)pkg)->palette);
	}
	if (key == S)
	{
		((package *)pkg)->palette->green -= 5;
		(*f)(mlx_ptr, win_ptr, mainmandel, ((package *)pkg)->palette);
	}
	if (key == D)
	{
		((package *)pkg)->palette->blue -= 5;
		(*f)(mlx_ptr, win_ptr, mainmandel, ((package *)pkg)->palette);
	}
}

int		key_press(int key, void *pkg)
{
	mandel	*mainmandel;

	mainmandel = ((package *)pkg)->mainmandel;
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
		key_driver(key, pkg, burningship_driver);
	}
	return (1);
}
