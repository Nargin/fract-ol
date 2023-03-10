/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: romaurel <romaurel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 12:14:01 by romaurel          #+#    #+#             */
/*   Updated: 2023/03/10 12:16:13 by romaurel         ###   ########.fr       */
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
	printf("x:%d, y:%d\n", x, y);
	if (keycode == ZP)
	{
		// convertir la position de la souris en une position sur la fractale
		// double newPosX = prog->f.cRe + (x - prog->pos.w / 2.0) / (0.5 * prog->pos.zoom * prog->pos.w) + prog->pos.moveX;
		// double newPosY = prog->f.cIm + (y - prog->pos.h / 2.0) / (0.5 * prog->pos.zoom * prog->pos.h) + prog->pos.moveY;

		prog->pos.zoom *= 1.25f;
		// prog->pos.moveX += (prog->f.cRe - newPosX) * 1.25f;
		// prog->pos.moveY += (prog->f.cIm - newPosY) * 1.25f;
		// if (x > prog->pos.w / 2)

	}
	if (keycode == ZM)
		prog->pos.zoom /= 1.25f;
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
