/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: romaurel <romaurel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 12:14:01 by romaurel          #+#    #+#             */
/*   Updated: 2023/03/11 13:00:04 by romaurel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int	end_p(t_prog *prog)
{
	mlx_destroy_image(prog->win.mlx, prog->win.img);
	mlx_destroy_window(prog->win.mlx, prog->win.mlx_win);
	exit(0);
}

int	move(int keycode, t_prog *prog)
{
	if (keycode == K_UP)
		prog->pos.movey -= .1f / prog->pos.zoom;
	if (keycode == K_DOWN)
		prog->pos.movey += .1f / prog->pos.zoom;
	if (keycode == K_LEFT)
		prog->pos.movex -= .1f / prog->pos.zoom;
	if (keycode == K_RIGHT)
		prog->pos.movex += .1f / prog->pos.zoom;
	return (1);
}

int	woom(int keycode, int x, int y, t_prog *prog)
{
	if (keycode == ZP)
	{
		prog->pos.zoom *= 1.25f;
		if (ZOF == 1)
		{
			if (x >= prog->pos.w / 2)
				prog->pos.movex += .15f / prog->pos.zoom;
			else
				prog->pos.movex -= .15f / prog->pos.zoom;
			if (y >= prog->pos.h / 2)
				prog->pos.movey += .15f / prog->pos.zoom;
			else
				prog->pos.movey -= .15f / prog->pos.zoom;
		}
	}
	if (keycode == ZM)
		prog->pos.zoom /= 1.25f;
	mlx_clear_window(prog->win.mlx, prog->win.mlx_win);
	fractal_island(prog->f.set, prog);
	mlx_put_image_to_window(prog->win.mlx, prog->win.mlx_win,
		prog->win.img, 0, 0);
	return (1);
}

void	change_reality(int keycode, t_prog *prog)
{
	if (keycode == A)
		prog->f.cre += .04;
	if (keycode == D)
		prog->f.cre -= .04;
	if (keycode == Z)
		prog->f.cim += .04;
	if (keycode == C)
		prog->f.cim -= .04;
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
	mlx_put_image_to_window(prog->win.mlx, prog->win.mlx_win,
		prog->win.img, 0, 0);
	return (1);
}
