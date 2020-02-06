/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yinzhang <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/27 08:28:19 by yinzhang          #+#    #+#             */
/*   Updated: 2020/01/27 12:08:38 by yinzhang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

double mapToReal(int x, int imageWidth, double minR, double maxR)
{
	double range = maxR - minR;
	return(x * (range / imageWidth) + minR); 
}

double mapToImaginary(int x, int imageWidth, double minI, double maxI)
{
	double range = maxI - minI;
	return(x * (range / imageWidth) + minI);
}

int findJulia(double a, double b, int max_iterations, mandel *mand)
{
	int i = 0;

	double zr = 0.0;
	double zi = 0.0;
	int flag = 0;

	zr = a * a - b * b;
	zi = 2 * a * b;
	while(i < max_iterations)
	{
		double tmp = zr * zr - zi * zi + mapToReal(mand->xmouse, mand->imageWidth, mand->realMin, mand->realMax);
		zi = 2 * zr * zi + mapToImaginary(mand->ymouse, mand->imageHeight, mand->imaginaryMin, mand->imaginaryMax);
		zr = tmp;	
		if (zr*zr + zi*zi > 4)
			break ;
		i++;
	}
	return(i);
}

void	julia_driver(void *mlx_ptr, void *win_ptr, mandel *mand, colors *palette)
{
	mlx_clear_window(mlx_ptr, win_ptr);
	
	int rando = mand->randseed;//rand();
	for(int y = 0; y < mand->imageHeight; y++)
	{
		for(int x = 0; x < mand->imageWidth; x++)
		{
			double cr = mapToReal(x, mand->imageWidth, mand->realMin, mand->realMax);
			double ci = mapToImaginary(y, mand->imageHeight, mand->imaginaryMin, mand->imaginaryMax);
			int n = findJulia(cr, ci, mand->iterations, mand);
			int r = ((n + palette->red) * rando % 256);
			int g = ((n + palette->green) * rando % 256);
			int b = ((n + palette->blue) * rando % 256);
			int rgb;
			rgb = (r << 16 | g << 8 | b);
			if (n < mand->iterations - 1)
				mlx_pixel_put(mlx_ptr, win_ptr, x, y, rgb);
		}
	}
}


int findMandelbrot(double cr, double ci, int max_iterations)
{
	int i = 0;

	double zr = 0;
	double zi = 0;
	while (i < max_iterations && zr * zr + zi * zi < 4)
	{
		double tmp = zr * zr - zi * zi + cr;
		zi = 2 * zi * zr + ci;
		zr = tmp;
		i++;
	}
	return(i);
}

void	mandelbrot_driver(void *mlx_ptr, void *win_ptr, mandel *mand, colors *palette)
{

	mlx_clear_window(mlx_ptr, win_ptr);
	int rando = mand->randseed;//rand();

	for(int y = 0 ;y < mand->imageHeight; y++)
	{
		for(int x = 0 ;x < mand->imageWidth; x++)
		{
			double cr = mapToReal(x, mand->imageWidth, mand->realMin, mand->realMax);
			double ci = mapToImaginary(y, mand->imageHeight, mand->imaginaryMin, mand->imaginaryMax);
			int n = findMandelbrot(cr, ci, mand->iterations);
			int r = ((n + palette->red) * rando % 256);
			int g = ((n + palette->green) * rando % 256);
			int b = ((n + palette->blue) * rando % 256);
			int rgb;
			rgb = (r << 16 | g << 8 | b);
			if (n < mand->iterations - 1)
				mlx_pixel_put(mlx_ptr, win_ptr, x, y, rgb);
		}
	}
}

int		ft_strcmp(char *s1, char *s2)
{
	int i;

	i = 0;
	while(s1[i] && s2[i] && s1[i] == s2[i])
		i++;
	return(s1[i] - s2[i]);
}

/*
void julia_keys(int key, package *pkg)
{
	void *mlx_ptr;
	void *win_ptr;
	mandel *mainMandel;

	mlx_ptr = ((package *)pkg)->mlx_ptr;
	win_ptr = ((package *)pkg)->win_ptr;
	mainMandel = ((package *)pkg)->mainMandel;


	//123 126 124 125 left up right down

	if (key == 53) //escape
		exit(1);
	//for zoomies later on
		if(key == 123) //left
	{
		mainMandel->realMin += (mainMandel->zoomscale * .25);
		mainMandel->realMax += (mainMandel->zoomscale * .25);
		julia_driver(mlx_ptr, win_ptr, mainMandel, ((package *)pkg)->palette);
	}
	if(key == 126) //up
	{
		//mainMandel->imaginaryMin *= .9;
		//mainMandel->imaginaryMax /= .9;
		mainMandel->imaginaryMin += mainMandel->zoomscale * .25;
		mainMandel->imaginaryMax += mainMandel->zoomscale *.25;
		//mainMandel->vertical -= 50;
		julia_driver(mlx_ptr, win_ptr, mainMandel, ((package *)pkg)->palette);
	}
	if(key == 124) //right
	{
		mainMandel->realMin -= mainMandel->zoomscale * .25;
		mainMandel->realMax -= mainMandel->zoomscale * .25;
		//mainMandel->realMin /= .9;
		//mainMandel->realMax *= .9;
		//mainMandel->horizontal += 50;
		julia_driver(mlx_ptr, win_ptr, mainMandel, ((package *)pkg)->palette);
	}
	if(key == 125) //down
	{
		mainMandel->imaginaryMin -= mainMandel->zoomscale *.25;
		mainMandel->imaginaryMax -= mainMandel->zoomscale *.25;
		//mainMandel->imaginaryMin /= -.9;
		//mainMandel->imaginaryMax *= -.9;
		//mainMandel->vertical += 50;		
		julia_driver(mlx_ptr, win_ptr, mainMandel, ((package *)pkg)->palette);
	}
	if (key == 31) //o xkey zoom in
	{
		mainMandel->realMin *= .9;
		mainMandel->realMax *= .9;
		mainMandel->imaginaryMin *= .9;
		mainMandel->imaginaryMax *= .9;
		mainMandel->zoomscale *= .9;
		julia_driver(mlx_ptr, win_ptr, mainMandel, ((package *)pkg)->palette);
	}
	if (key == 35) //p kxey zoom out
	{
		mainMandel->realMin /= .9;
		mainMandel->realMax /= .9;
		mainMandel->imaginaryMin /= .9;
		mainMandel->imaginaryMax /= .9;
		mainMandel->zoomscale /= .9;
		julia_driver(mlx_ptr, win_ptr, mainMandel, ((package *)pkg)->palette);
	}
	if (key == 31) //o xkey
	{
		mainMandel->realMin += .1;
		mainMandel->realMax -= .1;
		mainMandel->imaginaryMin += .1;
		mainMandel->imaginaryMax-= .1;
		julia_driver(mlx_ptr, win_ptr, mainMandel, ((package *)pkg)->palette);
	}
	if (key == 35) //p kxey
	{
		mainMandel->realMin+= .1;
		mainMandel->realMax-= .1;
		mainMandel->imaginaryMin+= .1;
		mainMandel->imaginaryMax-= .1;
		julia_driver(mlx_ptr, win_ptr, mainMandel, ((package *)pkg)->palette);
	}
	if (key == 12) //q
	{
		((package *)pkg)->palette->red += 5;
		julia_driver(mlx_ptr, win_ptr, mainMandel, ((package *)pkg)->palette);
	}
	if (key == 13) //w
	{
		((package *)pkg)->palette->green += 5;
		julia_driver(mlx_ptr, win_ptr, mainMandel, ((package *)pkg)->palette);
	}
	if (key == 14) //e
	{
		((package *)pkg)->palette->blue += 5;
		julia_driver(mlx_ptr, win_ptr, mainMandel, ((package *)pkg)->palette);
	}
	if (key == 0) //a
	{
		((package *)pkg)->palette->red -= 5;
		julia_driver(mlx_ptr, win_ptr, mainMandel, ((package *)pkg)->palette);
	}
	if (key == 1) //s
	{
		((package *)pkg)->palette->green -= 5;
		julia_driver(mlx_ptr, win_ptr, mainMandel, ((package *)pkg)->palette);
	}	
	if (key == 2) //d
	{
		((package *)pkg)->palette->blue -= 5;
		julia_driver(mlx_ptr, win_ptr, mainMandel, ((package *)pkg)->palette);
	}
}



void mandelbrot_keys(int key, package *pkg)
{
	void *mlx_ptr;
	void *win_ptr;
	mandel *mainMandel;

	mlx_ptr = ((package *)pkg)->mlx_ptr;
	win_ptr = ((package *)pkg)->win_ptr;
	mainMandel = ((package *)pkg)->mainMandel;
	int scale = (mainMandel->realMax - mainMandel->realMin);

	//printf("its working %d\n", key);
	//123 126 124 125 left up right down
	if (key == 53) //escape
		exit(1);
	if(key == 123) //left
	{
		//mainMandel->realMin *= .9;
		//mainMandel->realMax /= .9;
		mainMandel->realMin += (mainMandel->zoomscale * .25);
		mainMandel->realMax += (mainMandel->zoomscale * .25);
		//mainMandel->horizontal -= 50;
		mandelbrot_driver(mlx_ptr, win_ptr, mainMandel, ((package *)pkg)->palette);
	}
	if(key == 126) //up
	{
		//mainMandel->imaginaryMin *= .9;
		//mainMandel->imaginaryMax /= .9;
		mainMandel->imaginaryMin += mainMandel->zoomscale * .25;
		mainMandel->imaginaryMax += mainMandel->zoomscale *.25;
		//mainMandel->vertical -= 50;
		mandelbrot_driver(mlx_ptr, win_ptr, mainMandel, ((package *)pkg)->palette);
	}
	if(key == 124) //right
	{
		mainMandel->realMin -= mainMandel->zoomscale * .25;
		mainMandel->realMax -= mainMandel->zoomscale * .25;
		//mainMandel->realMin /= .9;
		//mainMandel->realMax *= .9;
		//mainMandel->horizontal += 50;
		mandelbrot_driver(mlx_ptr, win_ptr, mainMandel, ((package *)pkg)->palette);
	}
	if(key == 125) //down
	{
		mainMandel->imaginaryMin -= mainMandel->zoomscale *.25;
		mainMandel->imaginaryMax -= mainMandel->zoomscale *.25;
		//mainMandel->imaginaryMin /= -.9;
		//mainMandel->imaginaryMax *= -.9;
		//mainMandel->vertical += 50;		
		mandelbrot_driver(mlx_ptr, win_ptr, mainMandel, ((package *)pkg)->palette);
	}
	if (key == 31) //o xkey zoom in
	{
		mainMandel->realMin *= .9;
		mainMandel->realMax *= .9;
		mainMandel->imaginaryMin *= .9;
		mainMandel->imaginaryMax *= .9;
		mainMandel->zoomscale *= .9;
		mandelbrot_driver(mlx_ptr, win_ptr, mainMandel, ((package *)pkg)->palette);
	}
	if (key == 35) //p kxey zoom out
	{
		mainMandel->realMin /= .9;
		mainMandel->realMax /= .9;
		mainMandel->imaginaryMin /= .9;
		mainMandel->imaginaryMax /= .9;
		mainMandel->zoomscale /= .9;
		mandelbrot_driver(mlx_ptr, win_ptr, mainMandel, ((package *)pkg)->palette);
	}
	if (key == 12) //q
	{
		((package *)pkg)->palette->red += 5;
		mandelbrot_driver(mlx_ptr, win_ptr, mainMandel, ((package *)pkg)->palette);
	}
	if (key == 13) //w
	{
		((package *)pkg)->palette->green += 5;
		mandelbrot_driver(mlx_ptr, win_ptr, mainMandel, ((package *)pkg)->palette);
	}
	if (key == 14) //e
	{
		((package *)pkg)->palette->blue += 5;
		mandelbrot_driver(mlx_ptr, win_ptr, mainMandel, ((package *)pkg)->palette);
	}
	if (key == 0) //a
	{
		((package *)pkg)->palette->red -= 5;
		mandelbrot_driver(mlx_ptr, win_ptr, mainMandel, ((package *)pkg)->palette);
	}
	if (key == 1) //s
	{
		((package *)pkg)->palette->green -= 5;
		mandelbrot_driver(mlx_ptr, win_ptr, mainMandel, ((package *)pkg)->palette);
	}	
	if (key == 2) //d
	{
		((package *)pkg)->palette->blue -= 5;
		mandelbrot_driver(mlx_ptr, win_ptr, mainMandel, ((package *)pkg)->palette);
	}
}



int		key_press(int key, void *pkg)
{
	mandel *mainMandel;
	mainMandel = ((package *)pkg)->mainMandel;	

	if (mainMandel->type == JULIA)
	{
		julia_keys(key, (package *)pkg);
	}
	else if(mainMandel->type == MANDELBROT)
	{
		mandelbrot_keys(key, (package *)pkg);
	}
	return (1);
} */

int findBurningShip(double cr, double ci, int max_iterations)
{
	int i = 0;

	double zr = 0;
	double zi = 0;
	while (i < max_iterations && zr * zr + zi * zi < 4)
	{
		double tmp = zr * zr - zi * zi + cr;
		zi = fabs(2 * zi * zr + ci);
		zr = tmp;
		i++;
	}
	return(i);
}

void	burningship_driver(void *mlx_ptr, void *win_ptr, mandel *mand, colors *palette)
{

	mlx_clear_window(mlx_ptr, win_ptr);
	int rando = mand->randseed;//rand();

	for(int y = 0 ;y < mand->imageHeight; y++)
	{
		for(int x = 0 ;x < mand->imageWidth; x++)
		{
			double cr = mapToReal(x, mand->imageWidth, mand->realMin, mand->realMax);
			double ci = mapToImaginary(y, mand->imageHeight, mand->imaginaryMin, mand->imaginaryMax);
			int n = findBurningShip(cr, ci, mand->iterations);
			int r = ((n + palette->red) * rando % 256);
			int g = ((n + palette->green) * rando % 256);
			int b = ((n + palette->blue) * rando % 256);
			int rgb;
			rgb = (r << 16 | g << 8 | b);
			if (n < mand->iterations - 1)
				mlx_pixel_put(mlx_ptr, win_ptr, x, y, rgb);
		}
	}
}

void		key_driver(int key, void *pkg, void (* f)(void *mlx_ptr, void *win_ptr, mandel *mand, colors *palette))
{
	void *mlx_ptr;
	void *win_ptr;
	mandel *mainMandel;

	mlx_ptr = ((package *)pkg)->mlx_ptr;
	win_ptr = ((package *)pkg)->win_ptr;
	mainMandel = ((package *)pkg)->mainMandel;
	int scale = (mainMandel->realMax - mainMandel->realMin);

	if (key == 53) //esc
		exit(1);
	if(key == 123) //left
	{
		mainMandel->realMin += (mainMandel->zoomscale * .25);
		mainMandel->realMax += (mainMandel->zoomscale * .25);
		(*f)(mlx_ptr, win_ptr, mainMandel, ((package *)pkg)->palette);
	}
	if(key == 126) //up
	{
		mainMandel->imaginaryMin += mainMandel->zoomscale * .25;
		mainMandel->imaginaryMax += mainMandel->zoomscale *.25;
		(*f)(mlx_ptr, win_ptr, mainMandel, ((package *)pkg)->palette);
	}
	if(key == 124) //right
	{
		mainMandel->realMin -= mainMandel->zoomscale * .25;
		mainMandel->realMax -= mainMandel->zoomscale * .25;
		(*f)(mlx_ptr, win_ptr, mainMandel, ((package *)pkg)->palette);
	}
	if(key == 125) //down
	{
		mainMandel->imaginaryMin -= mainMandel->zoomscale *.25;
		mainMandel->imaginaryMax -= mainMandel->zoomscale *.25;
		(*f)(mlx_ptr, win_ptr, mainMandel, ((package *)pkg)->palette);
	}
	if (key == 31) //o xkey zoom in
	{
		mainMandel->realMin *= .9;
		mainMandel->realMax *= .9;
		mainMandel->imaginaryMin *= .9;
		mainMandel->imaginaryMax *= .9;
		mainMandel->zoomscale *= .9;
		(*f)(mlx_ptr, win_ptr, mainMandel, ((package *)pkg)->palette);
	}
	if (key == 35) //p kxey zoom out
	{
		mainMandel->realMin /= .9;
		mainMandel->realMax /= .9;
		mainMandel->imaginaryMin /= .9;
		mainMandel->imaginaryMax /= .9;
		mainMandel->zoomscale /= .9;
		(*f)(mlx_ptr, win_ptr, mainMandel, ((package *)pkg)->palette);
	}
	if (key == 12) //q
	{
		((package *)pkg)->palette->red += 5;
		(*f)(mlx_ptr, win_ptr, mainMandel, ((package *)pkg)->palette);
	}
	if (key == 13) //w
	{
		((package *)pkg)->palette->green += 5;
		(*f)(mlx_ptr, win_ptr, mainMandel, ((package *)pkg)->palette);
	}
	if (key == 14) //e
	{
		((package *)pkg)->palette->blue += 5;
		(*f)(mlx_ptr, win_ptr, mainMandel, ((package *)pkg)->palette);
	}
	if (key == 0) //a
	{
		((package *)pkg)->palette->red -= 5;
		(*f)(mlx_ptr, win_ptr, mainMandel, ((package *)pkg)->palette);
	}
	if (key == 1) //s
	{
		((package *)pkg)->palette->green -= 5;
		(*f)(mlx_ptr, win_ptr, mainMandel, ((package *)pkg)->palette);
	}	
	if (key == 2) //d
	{
		((package *)pkg)->palette->blue -= 5;
		(*f)(mlx_ptr, win_ptr, mainMandel, ((package *)pkg)->palette);
	}
}

int		key_press(int key, void *pkg)
{
	mandel *mainMandel;
	mainMandel = ((package *)pkg)->mainMandel;
	if (mainMandel->type == JULIA)
	{
		key_driver(key, pkg, julia_driver);
	}
	else if(mainMandel->type == MANDELBROT)
	{
		key_driver(key, pkg, mandelbrot_driver);
	}
	else if(mainMandel->type == BURNINGSHIP)
	{
		key_driver(key, pkg, burningship_driver);	
	}
	return (1);
}




int		mouse_move(int x, int y, package *pkg)
{
	mandel *mainMandel = pkg->mainMandel;
	void *mlx_ptr;
	void *win_ptr;

	mlx_ptr = ((package *)pkg)->mlx_ptr;
	win_ptr = ((package *)pkg)->win_ptr;
	mainMandel->xmouse = x;
	mainMandel->ymouse = y;
	julia_driver(mlx_ptr, win_ptr, mainMandel, ((package *)pkg)->palette);
	return (1);
}

mandel *mainMandelInit()
{
	mandel *ret;

	ret = malloc(sizeof(mandel));
	ret->imageWidth = 750;
	ret->imageHeight = 750;
	ret->iterations = 100;
	ret->realMin = -2.5;
	ret->realMax = 2.5;
	ret->imaginaryMin = -2.5;
	ret->imaginaryMax = 2.5;
	ret->xmouse = 2;
	ret->ymouse = 2;
	ret->horizontal = 0;
	ret->vertical = 0;
	ret->zoomscale = 1;
	ret->randseed = 50;
	return(ret);
}

void	fractal_driver(char *s)
{
	void *mlx_ptr;
	void *win_ptr;
	mandel *mainMandel;
	colors *palette;
	package pkg;

	palette = malloc(sizeof(colors));

	palette->red = 0;
	palette->green = 0;
	palette->blue = 0;

	mainMandel = mainMandelInit();
	mlx_ptr = mlx_init();
	win_ptr = mlx_new_window(mlx_ptr, 750, 750, "fractol beta");
	pkg.mlx_ptr = mlx_ptr;
	pkg.win_ptr = win_ptr;
	pkg.mainMandel = mainMandel;
	pkg.palette = palette;

	if(!ft_strcmp(s, "julia") || !ft_strcmp(s, "Julia"))
	{
		mainMandel->type = JULIA;
		mlx_key_hook(win_ptr, &key_press, &pkg);
		mlx_hook(win_ptr, 6, 0, &mouse_move, &pkg);
		julia_driver(mlx_ptr, win_ptr, mainMandel, palette);
		mlx_loop(mlx_ptr);
	}
	else if(!ft_strcmp(s, "mandelbrot") || !ft_strcmp(s, "Mandelbrot"))
	{
		mainMandel->type = MANDELBROT; 
		mandelbrot_driver(mlx_ptr, win_ptr, mainMandel, palette);
		mlx_key_hook(win_ptr, &key_press, &pkg);
		mlx_loop(mlx_ptr);
	}
	else if(!ft_strcmp(s, "burning ship") || !ft_strcmp(s, "Buring Ship"))
	{
		mainMandel->type = BURNINGSHIP;
		burningship_driver(mlx_ptr, win_ptr, mainMandel, palette);
		mlx_key_hook(win_ptr, &key_press, &pkg);
		mlx_loop(mlx_ptr);
	}
}

int		main(int argc, char **argv)
{
	if(argc == 2)
	{
		fractal_driver(argv[1]);
	}
	else
		printf("Usage: ./fractol Julia Mandelbrot OneMore\n");
}
