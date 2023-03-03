/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fract-ol.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: romaurel <romaurel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/17 21:59:02 by romaurel          #+#    #+#             */
/*   Updated: 2023/03/03 17:09:39 by robin            ###   ########.fr       */
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

void	my_mlx_pixel_put(t_win *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

int	main(void) {
	t_win	img;
	int		x;
	int		y;

	img.c.h = 720;
	img.c.w = 1280;

	//each iteration, it calculates: new = old*old + c, where c is a constant and old starts at current pixel
	//double cRe, cIm;           //real and imaginary part of the constant c, determinate shape of the Julia Set
	//double img.c.newRe, img.c.newIm, img.c.oldRe, img.c.oldIm;   //real and imaginary parts of new and old

	img.c.zoom = 1;
	img.c.moveX = 0;
	img.c.moveY = 0; //you can change these to zoom and change position

	img.mlx = mlx_init();
	img.mlx_win = mlx_new_window(img.mlx, img.c.w, img.c.h, "Fract-ol.jpg");
	img.img = mlx_new_image(img.mlx, img.c.w, img.c.h);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length, &img.endian);
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
	mlx_put_image_to_window(img.mlx, img.mlx_win, img.img, 0, 0);
	mlx_loop(img.mlx);
}
