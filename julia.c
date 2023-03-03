/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   julia.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: robin <robin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/03 22:01:17 by robin             #+#    #+#             */
/*   Updated: 2023/03/03 22:03:30 by robin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fract-ol.h"

int	pixel_farmer(int x, int y, t_var c)
{
	int		i;

	i = -1;
	c.newRe = 1.5 * (x - c.w / 2) / (0.5 * c.zoom * c.w) + c.moveX;
	c.newIm = (y - c.h / 2) / (0.5 * c.zoom * c.h) + c.moveY;
	while(++i < 400)
	{
		//remember value of previous iteration
		c.oldRe = c.newRe;
		c.oldIm = c.newIm;
		//the actual iteration, the real and imaginary part are calculated
		c.newRe = c.oldRe * c.oldRe - c.oldIm * c.oldIm + c.cRe;
		c.newIm = 2 * c.oldRe * c.oldIm + c.cIm;
		//if the point is outside the circle with radius 2: stop
		if((c.newRe * c.newRe + c.newIm * c.newIm) > 4)
			break;
	}
	return (i);
}

void	julia(t_win img)
{
    int		x;
	int		y;
    //pick some values for the constant c, this determines the shape of the Julia Set
	img.c.cRe = -0.7;
	img.c.cIm = 0.27015;

	//loop through every pixel
	y = -1;
	while (++y < img.c.h)
	{
		x = -1;
		while (++x < img.c.w)
			my_mlx_pixel_put(&img, x, y, pixel_farmer(x, y, img.c) * .3);
	}
}
