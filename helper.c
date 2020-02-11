/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yinzhang <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/06 10:17:46 by yinzhang          #+#    #+#             */
/*   Updated: 2020/02/06 10:17:47 by yinzhang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

double		map_to_real(int x, int imagewidth, double minr, double maxr)
{
	double range;

	range = maxr - minr;
	return (x * (range / imagewidth) + minr);
}

double		map_to_imaginary(int x, int imagewidth, double mini, double maxi)
{
	double range;

	range = maxi - mini;
	return (x * (range / imagewidth) + mini);
}

int			ft_strcmp(char *s1, char *s2)
{
	int i;

	i = 0;
	while (s1[i] && s2[i] && s1[i] == s2[i])
		i++;
	return (s1[i] - s2[i]);
}

t_mandel	*main_mandel_init(void)
{
	t_mandel *ret;

	ret = malloc(sizeof(t_mandel));
	ret->imagewidth = 750;
	ret->imageheight = 750;
	ret->iterations = 100;
	ret->realmin = -2.5;
	ret->realmax = 2.5;
	ret->imaginarymin = -2.5;
	ret->imaginarymax = 2.5;
	ret->xmouse = 2;
	ret->ymouse = 2;
	ret->horizontal = 0;
	ret->vertical = 0;
	ret->zoomscale = 1;
	ret->randseed = 50;
	return (ret);
}
