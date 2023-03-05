/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fract-ol.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: romaurel <romaurel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/17 21:59:02 by romaurel          #+#    #+#             */
/*   Updated: 2023/03/05 17:37:03 by romaurel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fract-ol.h"

int	move(int keycode, t_prog *prog)
{
	if (keycode == K_UP)
	{
		prog->pos.tempY -= 100 / prog->pos.zoom;
		prog->pos.moveY = prog->pos.tempY * prog->pos.zoom;
	}
	if (keycode == K_DOWN)
	{
		prog->pos.tempY += 100 / prog->pos.zoom;
		prog->pos.moveY = prog->pos.tempY * prog->pos.zoom;
	}
	if (keycode == K_LEFT)
	{
		prog->pos.tempX -= 100 / prog->pos.zoom;
		prog->pos.moveX = prog->pos.tempX * prog->pos.zoom;
	}
	if (keycode == K_RIGHT)
	{
		prog->pos.tempX += 100 / prog->pos.zoom;
		prog->pos.moveX = prog->pos.tempX * prog->pos.zoom;
	}
	mlx_clear_window(prog->win.mlx, prog->win.mlx_win);
	if (prog->f.set == 'j')
		julia(prog, prog->win);
	mlx_put_image_to_window(prog->win.mlx, prog->win.mlx_win, prog->win.img, 0, 0);
	return (1);
}

int	woom(int keycode, int x, int y, t_prog *prog)
{
	printf("x : %d, y : %d\n", x, y);
	if (keycode == 4)
	{
		prog->pos.tempX -= x / prog->pos.zoom;
		prog->pos.tempY -= y / prog->pos.zoom;
		prog->pos.zoom /= 2.;
		prog->pos.moveX = prog->pos.tempX * prog->pos.zoom;
		prog->pos.moveY = prog->pos.tempY * prog->pos.zoom;
	}
	if (keycode == 5)
	{
		prog->pos.tempX += x / prog->pos.zoom;
		prog->pos.tempY += y / prog->pos.zoom;
		prog->pos.zoom *= 2.;
		prog->pos.moveX = prog->pos.tempX * prog->pos.zoom;
		prog->pos.moveY = prog->pos.tempY * prog->pos.zoom;
	}
	mlx_clear_window(prog->win.mlx, prog->win.mlx_win);
	julia(prog, prog->win);
	mlx_put_image_to_window(prog->win.mlx, prog->win.mlx_win, prog->win.img, 0, 0);
	return (0);
}

void	p_start(char *set)
{
	t_prog	prog;

	// Dimension window
	prog.pos.w = 1920;
	prog.pos.h = 1080;

	// woom
	prog.pos.zoom = 1;
	prog.pos.moveX = 0;
	prog.pos.moveY = 0;
	prog.f.set = set[0];

	// julia
	prog.f.cIm = 0;
	prog.f.cRe = -1.476;

	prog.win.mlx = mlx_init();
	prog.win.mlx_win = mlx_new_window(prog.win.mlx, prog.pos.w, prog.pos.h, "Fract-ol");
	prog.win.img = mlx_new_image(prog.win.mlx, prog.pos.w, prog.pos.h);
	prog.win.addr = mlx_get_data_addr(prog.win.img, &prog.win.bits_per_pixel, &prog.win.line_length, &prog.win.endian);
	if (prog.f.set == 'j')
		julia(&prog, prog.win);
 	mlx_put_image_to_window(prog.win.mlx, prog.win.mlx_win, prog.win.img, 0, 0);
	mlx_mouse_hook(prog.win.mlx_win, woom, &prog.win);
	mlx_hook(prog.win.mlx_win, 17, 0, end_p, &prog.win);
	mlx_key_hook(prog.win.mlx_win, move, &prog.win);
	mlx_loop(prog.win.mlx);
}

int	main(void)
{
	p_start("j");
	return (0);
}
