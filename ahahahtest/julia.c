/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   julia.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: romaurel <romaurel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/03 22:01:17 by robin             #+#    #+#             */
/*   Updated: 2023/03/05 17:38:28 by romaurel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fract-ol.h"

int	pixel_farmer(int x, int y, t_prog *prog)
{
	int	i;
	t_fractal	f;

	i = -1;
	f.newRe = ((x + prog->pos.moveX) / (prog->pos.w * prog->pos.zoom) * 4) - 2;
	f.newIm = ((y + prog->pos.moveY) / (prog->pos.h * prog->pos.zoom) * 4) - 2;
	while(++i < MAX && (f.newRe * f.newRe + f.newIm * f.newIm) <= 4)
	{
		f.temp = f.newRe * f.newRe - f.newIm * f.newIm + prog->f.cRe;
		f.newIm = 2 * f.newRe * f.newIm - prog->f.cIm;
		f.newRe = f.temp;
	}
	return (i);
}

void	julia(t_prog *prog, t_win win)
{
    int		x;
	int		y;

	y = -1;
	while (++y < prog->pos.h)
	{
		x = -1;
		while (++x < prog->pos.w)
		{
			my_mlx_pixel_put(&win, x, y, pixel_farmer(x, y, prog) * 3);
		}
	}
}
