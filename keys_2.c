/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys_2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yinzhang <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/06 11:59:53 by yinzhang          #+#    #+#             */
/*   Updated: 2020/02/06 11:59:54 by yinzhang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	key_driver5(int key, void *pkg,
	void (*f)(void *mlx_ptr, void *win_ptr, mandel *mand, colors *palette))
{
	void	*mlx_ptr;
	void	*win_ptr;
	mandel	*mainmandel;

	mlx_ptr = ((package *)pkg)->mlx_ptr;
	win_ptr = ((package *)pkg)->win_ptr;
	mainmandel = ((package *)pkg)->mainmandel;
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

void	key_driver4(int key, void *pkg,
	void (*f)(void *mlx_ptr, void *win_ptr, mandel *mand, colors *palette))
{
	void	*mlx_ptr;
	void	*win_ptr;
	mandel	*mainmandel;

	mlx_ptr = ((package *)pkg)->mlx_ptr;
	win_ptr = ((package *)pkg)->win_ptr;
	mainmandel = ((package *)pkg)->mainmandel;
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
}
