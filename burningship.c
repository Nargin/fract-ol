/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   burningship.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: romaurel <romaurel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/08 17:11:29 by romaurel          #+#    #+#             */
/*   Updated: 2023/03/11 12:10:36 by romaurel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int	sea_of_pixels(int x, int y, t_prog *prog)
{
	t_fractal	f;
	int			i;

	f.newre = 0;
	f.newim = 0;
	i = -1;
	f.cre = x / (prog->pos.w * prog->pos.zoom)
		* 2.47 - 1.5 + prog->pos.movex;
	f.cim = y / (prog->pos.h * prog->pos.zoom)
		* 2.24 - 1.12 + prog->pos.movey;
	while (++i < MAX && (f.newre * f.newre + f.newim * f.newim) < 4)
	{
		f.oldre = f.newre;
		f.oldim = f.newim;
		f.newre = f.oldre * f.oldre - f.oldim * f.oldim + f.cre;
		f.newim = 2 * fabs(f.oldre * f.oldim) + f.cim;
	}
	return (i);
}

void	burningship(t_prog *prog, t_win win)
{
	int	x;
	int	y;
	int	i;

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
