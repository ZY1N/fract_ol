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

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include "minilibx_macos/mlx.h"
# include <math.h>

# define MANDELBROT 1
# define BURNINGSHIP 2
# define JULIA 0
# define ESC 53
# define LEFT 123
# define UP 126
# define RIGHT 124
# define DOWN 125
# define ZOOM_IN 31
# define ZOOM_OUT 35
# define Q 12
# define W 13
# define E 14
# define A 0
# define S 1
# define D 2

typedef struct	s_mandel
{
	int		imagewidth;
	int		imageheight;
	int		iterations;
	double	realmin;
	double	realmax;
	double	imaginarymin;
	double	imaginarymax;
	int		xmouse;
	int		ymouse;
	int		type;
	int		horizontal;
	int		vertical;
	int		randseed;
	double	zoomscale;
}				t_mandel;

typedef struct	s_colors
{
	int red;
	int green;
	int blue;
}				t_colors;

typedef struct	s_package
{
	void	*mlx_ptr;
	void	*win_ptr;
	t_mandel	*mainmandel;
	t_colors	*palette;
	int		xmouse;
	int		ymouse;
}				t_package;

double			map_to_real(int x, int imagewidth, double minr, double maxr);
double			map_to_imaginary(int x, int imagewidth,
					double mini, double maxi);
int				ft_strcmp(char *s1, char *s2);
t_mandel			*main_mandel_init();
void			key_driver(int key, void *pkg, void (*f)(void *mlx_ptr,
					void *win_ptr, t_mandel *mand, t_colors *palette));
int				key_press(int key, void *pkg);
void			julia_driver(void *mlx_ptr, void *win_ptr,
					t_mandel *mand, t_colors *p);
void			bship_driver(void *mlx_ptr, void *win_ptr,
					t_mandel *mand, t_colors *p);
void			key_driver5(int key, void *pkg,
void			(*f)(void *mlx_ptr, void *win_ptr, t_mandel *mand,
					t_colors *palette));
void			key_driver4(int key, void *pkg,
void			(*f)(void *mlx_ptr, void *win_ptr, t_mandel *mand,
					t_colors *palette));
int				findjulia(double a, double b, int max_iterations, t_mandel *mand);
int				findburningship(double cr, double ci, int max_iterations);
void			burningship_driver(void *mlx_ptr, void *win_ptr,
					t_mandel *mand, t_colors *p);
int				findmandelbrot(double cr, double ci, int max_iterations);
void			mandelbrot_driver(void *mlx_ptr, void *win_ptr,
					t_mandel *mand, t_colors *p);
void			fill_colors(t_colors **palette);
t_package		fill_pkg(t_mandel *mainmandel, t_colors *p, void *mlx_ptr,
					void *win_ptr);
void			free_things(t_mandel *mainmandel, t_colors *p,
					void *mlx_ptr, void *win_ptr);
void			init_mlx_win(void **mlx_ptr, void **win_ptr);
void			go_to_driver(t_mandel *mainmandel, void *mlx_ptr,
					void *win_ptr, t_colors *p);
#endif
