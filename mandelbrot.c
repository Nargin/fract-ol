/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mandelbrot.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: romaurel <romaurel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 14:28:02 by romaurel          #+#    #+#             */
/*   Updated: 2023/03/08 19:34:52 by romaurel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fract-ol.h"

int	pixelitito(int x, int y, t_prog *prog)
{
	int 		i;
	t_fractal	f;
	double		pr;
	double		pi;

	i = -1;
	f.newRe = 0;
	f.newIm = 0;
    pr = 1.5 * (x - prog->pos.w / 2) / (0.5 * prog->pos.zoom * prog->pos.w) + prog->pos.moveX;
    pi = (y - prog->pos.h / 2) / (0.5 * prog->pos.zoom * prog->pos.h) + prog->pos.moveY;
	while (++i < MAX && (f.newRe * f.newRe + f.newIm * f.newIm) < 4)
	{
		//remember value of previous iteration
		f.oldRe = f.newRe;
		f.oldIm = f.newIm;
		//the actual iteration, the real and imaginary part are calculated
		f.newRe = f.oldRe * f.oldRe - f.oldIm * f.oldIm + pr;
		f.newIm = 2 * f.oldRe * f.oldIm + pi;
		//if the point is outside the circle with radius 2: stop
	}
	return (i);
}

void	mandelbrot(t_prog *prog, t_win win)
{
	int	y;
	int	x;

	y = -1;
    while (++y < prog->pos.h)
    {
		x = -1;
		while (++x < prog->pos.w)
    	{
			my_mlx_pixel_put(&win, x, y, prog->f.color * pixelitito(x, y, prog));
			if (pixelitito(x, y, prog) >= MAX)
			 	my_mlx_pixel_put(&win, x, y, 0);
		}
	}
}