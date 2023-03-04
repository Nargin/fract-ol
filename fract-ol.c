/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fract-ol.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: romaurel <romaurel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/17 21:59:02 by romaurel          #+#    #+#             */
/*   Updated: 2023/03/04 18:36:40 by romaurel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fract-ol.h"

int	end_p(t_win w)
{
	mlx_destroy_image(w.mlx, w.mlx_win);
	mlx_destroy_window(w.mlx, w.mlx_win);
	mlx_loop_end(w.mlx);
	exit(0);
}

void	my_mlx_pixel_put(t_win *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

int	move(int keycode, t_win *w)
{
	if (keycode == K_UP)
		w->c.moveY -= 0.1f / w->c.zoom;
	if (keycode == K_DOWN)
		w->c.moveY += 0.1f / w->c.zoom;
	if (keycode == K_LEFT)
		w->c.moveX -= 0.1f / w->c.zoom;
	if (keycode == K_RIGHT)
		w->c.moveX += 0.1f / w->c.zoom;
	mlx_clear_window(w->mlx, w->mlx_win);
	if (w->set == 'j')
		julia(*w);
	mlx_put_image_to_window(w->mlx, w->mlx_win, w->img, 0, 0);
	return (1);
}

int	woom(int keycode, int x, int y, t_win *w)
{
	(void) x;
	(void) y;
	if (keycode == 4)
		w->c.zoom += .1f;
	if (keycode == 5)
		w->c.zoom -= .1f;
	mlx_clear_window(w->mlx, w->mlx_win);
	if (w->set == 'j')
		julia(*w);
	mlx_put_image_to_window(w->mlx, w->mlx_win, w->img, 0, 0);
	return (1);
}

void	p_start(char *set)
{
	t_win	w;

	// Dimension window
	w.c.w = 1280;
	w.c.h = 720;

	// woom
	w.c.zoom = 1;
	w.c.moveX = 0;
	w.c.moveY = 0;
	w.set = set[0];

	w.mlx = mlx_init();
	w.mlx_win = mlx_new_window(w.mlx, w.c.w, w.c.h, "Fract-ol");
	w.img = mlx_new_image(w.mlx, w.c.w, w.c.h);
	w.addr = mlx_get_data_addr(w.img, &w.bits_per_pixel, &w.line_length, &w.endian);
	if (w.set == 'j')
		julia(w);
 	mlx_put_image_to_window(w.mlx, w.mlx_win, w.img, 0, 0);
	mlx_mouse_hook(w.mlx_win, woom, &w);
	mlx_hook(w.mlx_win, 17, 0, end_p, &w);

	mlx_key_hook(w.mlx_win, move, &w);
	mlx_loop(w.mlx);
}

int	main(void)
{
	p_start("j");
	return (0);
}
