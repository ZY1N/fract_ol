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

double	map_to_real(int x, int imagewidth, double minr, double maxr)
{
	double range;

	range = maxr - minr;
	return (x * (range / imagewidth) + minr);
}

double	map_to_imaginary(int x, int imagewidth, double mini, double maxi)
{
	double range;

	range = maxi - mini;
	return (x * (range / imagewidth) + mini);
}

int		ft_strcmp(char *s1, char *s2)
{
	int i;

	i = 0;
	while (s1[i] && s2[i] && s1[i] == s2[i])
		i++;
	return (s1[i] - s2[i]);
}

mandel	*main_mandel_init(void)
{
	mandel *ret;

	ret = malloc(sizeof(mandel));
	ret->imagewidth = 750;
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
	return (ret);
}
