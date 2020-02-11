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
	void (*f)(void *mlx_ptr, void *win_ptr, t_mandel *mand, t_colors *palette))
{
	void	*mlx_ptr;
	void	*win_ptr;
	t_mandel	*mainmandel;

	mlx_ptr = ((t_package *)pkg)->mlx_ptr;
	win_ptr = ((t_package *)pkg)->win_ptr;
	mainmandel = ((t_package *)pkg)->mainmandel;
	if (key == A)
	{
		((t_package *)pkg)->palette->red -= 5;
		(*f)(mlx_ptr, win_ptr, mainmandel, ((t_package *)pkg)->palette);
	}
	if (key == S)
	{
		((t_package *)pkg)->palette->green -= 5;
		(*f)(mlx_ptr, win_ptr, mainmandel, ((t_package *)pkg)->palette);
	}
	if (key == D)
	{
		((t_package *)pkg)->palette->blue -= 5;
		(*f)(mlx_ptr, win_ptr, mainmandel, ((t_package *)pkg)->palette);
	}
}

void	key_driver4(int key, void *pkg,
	void (*f)(void *mlx_ptr, void *win_ptr, t_mandel *mand, t_colors *palette))
{
	void	*mlx_ptr;
	void	*win_ptr;
	t_mandel	*mainmandel;

	mlx_ptr = ((t_package *)pkg)->mlx_ptr;
	win_ptr = ((t_package *)pkg)->win_ptr;
	mainmandel = ((t_package *)pkg)->mainmandel;
	if (key == Q)
	{
		((t_package *)pkg)->palette->red += 5;
		(*f)(mlx_ptr, win_ptr, mainmandel, ((t_package *)pkg)->palette);
	}
	if (key == W)
	{
		((t_package *)pkg)->palette->green += 5;
		(*f)(mlx_ptr, win_ptr, mainmandel, ((t_package *)pkg)->palette);
	}
	if (key == E)
	{
		((t_package *)pkg)->palette->blue += 5;
		(*f)(mlx_ptr, win_ptr, mainmandel, ((t_package *)pkg)->palette);
	}
}
