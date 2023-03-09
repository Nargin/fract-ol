/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   burningship.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: romaurel <romaurel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/08 17:11:29 by romaurel          #+#    #+#             */
/*   Updated: 2023/03/09 11:39:07 by romaurel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fract-ol.h"

int sea_of_pixels(int x, int y, t_prog *prog)
{
	t_fractal	f;
	int			i;

	f.newRe = 0;
	f.newIm = 0;
	i = -1;
	f.cRe = x / (prog->pos.w * prog->pos.zoom)
		* 2.47 - 1.5 + prog->pos.moveX;
	f.cIm = y / (prog->pos.h * prog->pos.zoom)
		* 2.24 - 1.12 + prog->pos.moveY;
	while (++i < MAX && (f.newRe * f.newRe + f.newIm * f.newIm) < 4)
	{
		f.oldRe = f.newRe;
		f.oldIm = f.newIm;
		f.newRe = f.oldRe * f.oldRe - f.oldIm * f.oldIm + f.cRe;
		f.newIm = 2 * fabs(f.oldRe * f.oldIm) + f.cIm;
	}
	return (i);
}

void    burningship(t_prog *prog, t_win win)
{
	int x;
	int y;
	int i;

	y = -1;
	while (++y < prog->pos.h)
	{
		x = -1;
		while (++x < prog->pos.w)
		{
			i = sea_of_pixels(x, y, prog);
			if (i == MAX)
				my_mlx_pixel_put(&win, x, y, 0x000000);
			else
				my_mlx_pixel_put(&win, x, y, i * prog->f.color);
		}
	}
}