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

/*
void	fill_colors(colors **palette)
{
	*palette = malloc(sizeof(colors));
	(*palette)->red = 0;
	(*palette)->green = 0;
	(*palette)->blue = 0;
} */


void	fill_colors(colors *palette, colors **palette2)
{
	printf("fill color %lu\n", *palette2);
	*palette2 = malloc(sizeof(colors));
	(*palette2)->red = 0;
	(*palette2)->green = 0;
	(*palette2)->blue = 0;
}

package	fill_pkg(mandel *mainmandel, colors *p, void *mlx_ptr, void *win_ptr)
{
	package pkg;

	pkg.mlx_ptr = mlx_ptr;
	pkg.win_ptr = win_ptr;
	pkg.mainmandel = mainmandel;
	pkg.palette = p;
	return (pkg);
}

void	free_things(mandel *mainmandel, colors *p, void *mlx_ptr, void *win_ptr)
{
	free(mainmandel);
	free(p);
	free(win_ptr);
	free(mlx_ptr);
}
