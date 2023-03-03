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

void	my_mlx_pixel_put(t_win *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

void	p_start(char *set)
{
	t_win	img;

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
	if (set[0] == 'J' || set[0] == 'j')
		julia(img);
	mlx_put_image_to_window(img.mlx, img.mlx_win, img.img, 0, 0);
	mlx_loop(img.mlx);
}

int	main(void)
{
	p_start("julia");
	return (0);
}
