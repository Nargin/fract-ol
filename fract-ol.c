/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fract-ol.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: romaurel <romaurel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/17 21:59:02 by romaurel          #+#    #+#             */
/*   Updated: 2023/03/04 14:43:49 by romaurel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fract-ol.h"

int	end_p(t_win img)
{
	mlx_destroy_image(img.mlx, img.mlx_win);
	mlx_destroy_window(img.mlx, img.mlx_win);
	mlx_loop_end(img.mlx);
	exit(0);
}

void	my_mlx_pixel_put(t_win *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

int	move(int keycode, t_win *img)
{
	if (keycode == K_UP)
		img->c.moveY -= 0.1f / img->c.zoom;
	if (keycode == K_DOWN)
		img->c.moveY += 0.1f / img->c.zoom;
	if (keycode == K_LEFT)
		img->c.moveX -= 0.1f / img->c.zoom;
	if (keycode == K_RIGHT)
		img->c.moveX += 0.1f / img->c.zoom;
	mlx_clear_window(img->mlx, img->mlx_win);
	if (img->set == 'j')
		julia(*img);
	mlx_put_image_to_window(img->mlx, img->mlx_win, img->img, 0, 0);
	return (1);
}

int	woom(int keycode, int x, int y, t_win *img)
{
	(void) x;
	(void) y;
	if (keycode == 4)
		img->c.zoom += .1f;
	if (keycode == 5)
		img->c.zoom -= .1f;
	mlx_clear_window(img->mlx, img->mlx_win);
	if (img->set == 'j')
		julia(*img);
	mlx_put_image_to_window(img->mlx, img->mlx_win, img->img, 0, 0);
	return (1);
}

void	p_start(char *set)
{
	t_win	img;

	// Dimension window
	img.c.w = 1280;
	img.c.h = 720;

	// woom
	img.c.zoom = 1;
	img.c.moveX = 0;
	img.c.moveY = 0;
	img.set = set[0];

	img.mlx = mlx_init();
	img.mlx_win = mlx_new_window(img.mlx, img.c.w, img.c.h, "Fract-ol");
	img.img = mlx_new_image(img.mlx, img.c.w, img.c.h);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length, &img.endian);
	if (img.set == 'j')
		julia(img);
 	mlx_put_image_to_window(img.mlx, img.mlx_win, img.img, 0, 0);
	mlx_mouse_hook(img.mlx_win, woom, &img);
	mlx_hook(img.mlx_win, 17, 0, end_p, &img);
	mlx_key_hook(img.mlx_win, move, &img);
	mlx_loop(img.mlx);
}

int	main(void)
{
	p_start("j");
	return (0);
}
