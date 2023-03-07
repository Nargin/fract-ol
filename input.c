/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: romaurel <romaurel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 12:14:01 by romaurel          #+#    #+#             */
/*   Updated: 2023/03/07 18:38:02 by romaurel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fract-ol.h"

int	end_p(int k, t_prog *prog)
{
	if (k == Q)
	{
		if (prog->f.color == 0x0009EE10)
			prog->f.color = 0x00EE4709;
		else if (prog->f.color == 0x00EE4709)
			prog->f.color = 0x0009EEE7;
		else if (prog->f.color == 0x0009EEE7)
			prog->f.color = 0x00EE0982;
		else if (prog->f.color == 0x00EE0982)
			prog->f.color = 0x009C31EA;
		else if (prog->f.color == 0x009C31EA)
			prog->f.color = 0x000FAF77;
		else if (prog->f.color == 0x000FAF77)
			prog->f.color = 0;
	}
	else
	{
		mlx_destroy_image(prog->win.mlx, prog->win.img);
		mlx_destroy_window(prog->win.mlx, prog->win.mlx_win);
		exit(0);
	}
	return (1);
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
	(void) x;
	(void) y;
	if (keycode == ZP)
	{
		
		prog->pos.zoom *= 1.25f;

	}
	if (keycode == ZM)
	{

	}
	printf("zoom : %Lf\n", prog->pos.zoom);
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
	if (k == ESC || k == Q)
		end_p(k, prog);
	if (k == R)
		prog->pos.zoom = 1;
	mlx_clear_window(prog->win.mlx, prog->win.mlx_win);
	fractal_island(prog->f.set, prog);
	mlx_put_image_to_window(prog->win.mlx, prog->win.mlx_win, prog->win.img, 0, 0);
	return (1);
}
