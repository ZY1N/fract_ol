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

typedef struct mandel{
    int imageWidth;
    int imageHeight;
    int iterations;

    double realMin;
    double realMax;
    double imaginaryMin;
    double imaginaryMax;
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
} package;

#endif
