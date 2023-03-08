/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: romaurel <romaurel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 12:14:01 by romaurel          #+#    #+#             */
/*   Updated: 2023/03/08 20:14:36 by romaurel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fract-ol.h"

int	end_p(t_prog *prog)
{
	mlx_destroy_image(prog->win.mlx, prog->win.img);
	mlx_destroy_window(prog->win.mlx, prog->win.mlx_win);
	exit(0);
}

int	move(int keycode, t_prog *prog)
{
	if (keycode == K_UP)
		prog->pos.moveY -= .1f / prog->pos.zoom;
	if (keycode == K_DOWN)
		prog->pos.moveY += .1f / prog->pos.zoom;
	if (keycode == K_LEFT)
		prog->pos.moveX -= .1f / prog->pos.zoom;
	if (keycode == K_RIGHT)
		prog->pos.moveX += .1f / prog->pos.zoom;
	return (1);
}

int	woom(int keycode, int x, int y, t_prog *prog)
{
	double pre_zoom_x;
	double pre_zoom_y;
	double post_zoom_x;
	double post_zoom_y;

	if (keycode == ZP)
	{
		pre_zoom_x = (x - (double)prog->pos.w / 2) / prog->pos.zoom - prog->pos.moveX;
		pre_zoom_y = (y - (double)prog->pos.h / 2) / prog->pos.zoom - prog->pos.moveY;
		prog->pos.zoom *= 1.25f;
		post_zoom_x = (x - (double)prog->pos.w / 2) / prog->pos.zoom - prog->pos.moveX;
		post_zoom_y = (y - (double)prog->pos.h / 2) / prog->pos.zoom - prog->pos.moveY;
		prog->pos.moveX += (post_zoom_x - pre_zoom_x) * prog->pos.zoom / 1.25f;
		prog->pos.moveY += (post_zoom_y - pre_zoom_y) * prog->pos.zoom / 1.25f;
	}
	if (keycode == ZM)
	{
		prog->pos.zoom /= 1.25f;
	}
	//printf("zoom : %Lf\n", prog->pos.zoom);
	mlx_clear_window(prog->win.mlx, prog->win.mlx_win);
	fractal_island(prog->f.set, prog);
	mlx_put_image_to_window(prog->win.mlx, prog->win.mlx_win, prog->win.img, 0, 0);
	return (1);
}

void	change_reality(int keycode, t_prog *prog)
{
	if (keycode == A)
		prog->f.cRe += .04;
	if (keycode == D)
		prog->f.cRe -= .04;
	if (keycode == Z)
		prog->f.cIm += .04;
	if (keycode == C)
		prog->f.cIm -= .04;
}
int	input(int k, t_prog *prog)
{
	// printf("%d\n", k);
	if (k >= K_LEFT && k <= K_DOWN)
		move(k, prog);
	if (key(k, A) || key(k, D))
		change_reality(k, prog);
	if (key(k, Z) || key(k, C))
		change_reality(k, prog);
	if (k == ESC)
		end_p(prog);
	if (k == Q)
		zero_is_bad(prog);
	if (k == R)
		prog->pos.zoom = 1;
	mlx_clear_window(prog->win.mlx, prog->win.mlx_win);
	fractal_island(prog->f.set, prog);
	mlx_put_image_to_window(prog->win.mlx, prog->win.mlx_win, prog->win.img, 0, 0);
	return (1);
}
