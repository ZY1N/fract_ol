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

typedef struct mandel{
    int imageWidth;
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
    mandel *mainMandel;
    colors *palette;
    int     xmouse;
    int     ymouse;

} package;

#endif
