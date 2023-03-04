/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   julia.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: romaurel <romaurel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/03 22:01:17 by robin             #+#    #+#             */
/*   Updated: 2023/03/04 15:13:22 by romaurel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fract-ol.h"

int	pixel_farmer(int x, int y, t_win img)
{
	t_fractal	j;

	j.cIm = 0;
	j.cRe = -1.476;
	j.i = -1;
	j.newRe = 1.5 * (x - img.c.w / 2) / (0.5 * img.c.zoom * img.c.w) + img.c.moveX;
	j.newIm = (y - img.c.h / 2) / (0.5 * img.c.zoom * img.c.h) + img.c.moveY;
	while(++j.i < 100 && (j.newRe * j.newRe + j.newIm * j.newIm) <= 4)
	{
		//remember value of previous iteration
		j.oldRe = j.newRe;
		j.oldIm = j.newIm;
		//the actual iteration, the real and imaginary part are calculated
		j.newRe = j.oldRe * j.oldRe - j.oldIm * j.oldIm + j.cRe;
		j.newIm = 2 * j.oldRe * j.oldIm + j.cIm;
	}
	return (j.i);
}

void	julia(t_win img)
{
    int		x;
	int		y;

	y = -1;
	while (++y < img.c.h)
	{
		x = -1;
		while (++x < img.c.w)
		{
			my_mlx_pixel_put(&img, x, y, pixel_farmer(x, y, img) * 3);
		}
	}
}
