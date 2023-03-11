/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mandelbrot.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: romaurel <romaurel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 14:28:02 by romaurel          #+#    #+#             */
/*   Updated: 2023/03/11 12:07:25 by romaurel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int	pixelitito(int x, int y, t_prog *prog)
{
	int			i;
	t_fractal	f;
	double		pr;
	double		pi;

	i = -1;
	f.newre = 0;
	f.newim = 0;
	pr = 1.5 * (x - prog->pos.w / 2) / (0.5 * prog->pos.zoom * prog->pos.w)
		+ prog->pos.movex;
	pi = (y - prog->pos.h / 2) / (0.5 * prog->pos.zoom * prog->pos.h)
		+ prog->pos.movey;
	while (++i < MAX && (f.newre * f.newre + f.newim * f.newim) < 4)
	{
		f.oldre = f.newre;
		f.oldim = f.newim;
		f.newre = f.oldre * f.oldre - f.oldim * f.oldim + pr;
		f.newim = 2 * f.oldre * f.oldim + pi;
	}
	return (i);
}

void	mandelbrot(t_prog *prog, t_win win)
{
	int	y;
	int	x;
	int	i;

	y = -1;
	while (++y < prog->pos.h)
	{
		x = -1;
		while (++x < prog->pos.w)
		{
			i = pixelitito(x, y, prog);
			if (i == MAX)
				my_mlx_pixel_put(&win, x, y, 0);
			else
				my_mlx_pixel_put(&win, x, y, i * prog->f.color);
		}
	}
}
