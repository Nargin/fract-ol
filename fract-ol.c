/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fract-ol.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: romaurel <romaurel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/17 21:59:02 by romaurel          #+#    #+#             */
/*   Updated: 2023/03/07 18:50:12 by romaurel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fract-ol.h"

void	fractal_island(char c, t_prog *prog)
{
	if (c == 'j')
		julia(prog, prog->win);
	if (c == 'm')
		mandelbrot(prog, prog->win);
	//if (c == 'b')
	//	buddhabrot(prog, prog->win);
}

void	p_start(char set)
{
	t_prog	prog;

	// Dimension window
	prog.pos.w = 700;
	prog.pos.h = 540;

	// woom
	prog.pos.zoom = 1;
	prog.pos.moveX = 0;
	prog.pos.moveY = 0;
	prog.f.set = set;
	prog.f.color = 0x0009EE10;

	// julia
	prog.f.cIm = 0;
	prog.f.cRe = -1.476;

	prog.win.mlx = mlx_init();
	prog.win.mlx_win = mlx_new_window(prog.win.mlx, prog.pos.w, prog.pos.h, "Fract-ol");
	prog.win.img = mlx_new_image(prog.win.mlx, prog.pos.w, prog.pos.h);
	prog.win.addr = mlx_get_data_addr(prog.win.img, &prog.win.bits_per_pixel, &prog.win.line_length, &prog.win.endian);
	fractal_island(prog.f.set, &prog);
	mlx_mouse_hook(prog.win.mlx_win, woom, &prog.win);
	mlx_hook(prog.win.mlx_win, 17, 0, end_p, &prog.win);
	mlx_key_hook(prog.win.mlx_win, input, &prog.win);
	mlx_loop(prog.win.mlx);
}

int	main(void)
{
	p_start('j');
	return (0);
}
