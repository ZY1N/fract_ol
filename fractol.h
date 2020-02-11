/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yinzhang <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/30 11:36:19 by yinzhang          #+#    #+#             */
/*   Updated: 2020/01/30 11:36:20 by yinzhang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
# define FRACTOL_H

#include <stdio.h>
#include <stdlib.h>
#include "minilibx_macos/mlx.h"
#include <math.h>

#define BURNINGSHIP 2
#define MANDELBROT 1
#define JULIA 0
#define ESC 53
#define LEFT 123
#define UP 126
#define RIGHT 124
#define DOWN 125
#define ZOOM_IN 31
#define ZOOM_OUT 35
#define Q 12
#define W 13
#define E 14
#define A 0
#define S 1
#define D 2

typedef struct mandel{
    int imagewidth;
    int imageHeight;
    int iterations;

    double realMin;
    double realMax;
    double imaginaryMin;
    double imaginaryMax;

    int     xmouse;
    int     ymouse;
    int     type;

    int horizontal;
    int vertical;
    int randseed;

    double zoomscale;
} mandel;

typedef struct colors{
    int red;
    int green;
    int blue;
} colors;

typedef struct package{
    void *mlx_ptr;
    void *win_ptr;
    mandel *mainmandel;
    colors *palette;
    int     xmouse;
    int     ymouse;

} package;

double	map_to_real(int x, int imagewidth, double minr, double maxr);
double	map_to_imaginary(int x, int imagewidth, double mini, double maxi);
int		ft_strcmp(char *s1, char *s2);
mandel *main_mandel_init();
void		key_driver(int key, void *pkg, void (* f)(void *mlx_ptr, void *win_ptr, mandel *mand, colors *palette));
int key_press(int key, void *pkg);
void	julia_driver(void *mlx_ptr, void *win_ptr, mandel *mand, colors *palette);
void	mandelbrot_driver(void *mlx_ptr, void *win_ptr, mandel *mand, colors *palette);
void	bship_driver(void *mlx_ptr, void *win_ptr, mandel *mand, colors *palette);
void	key_driver5(int key, void *pkg,
	void (*f)(void *mlx_ptr, void *win_ptr, mandel *mand, colors *palette));
void	key_driver4(int key, void *pkg,
	void (*f)(void *mlx_ptr, void *win_ptr, mandel *mand, colors *palette));
   int		findjulia(double a, double b, int max_iterations, mandel *mand);
int findBurningShip(double cr, double ci, int max_iterations);
void	burningship_driver(void *mlx_ptr, void *win_ptr, mandel *mand, colors *p);
int findmandelbrot(double cr, double ci, int max_iterations);
void	mandelbrot_driver(void *mlx_ptr, void *win_ptr, mandel *mand, colors *p);
//colors *	fill_colors();
//void 	fill_colors(colors **palette);
void	fill_colors(colors *p, colors **p2);
//void	fill_pkg(mandel *mainmandel, colors *palette, package *pkg);
package	fill_pkg(mandel *mainmandel, colors *p, void *mlx_ptr, void *win_ptr);
void	free_things(mandel *mainmandel, colors *p, void *mlx_ptr, void *win_ptr);

#endif
