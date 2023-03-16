/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fract-ol.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: romaurel <romaurel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/17 21:59:02 by romaurel          #+#    #+#             */
/*   Updated: 2023/03/16 16:01:37 by romaurel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	putstr(char *s)
{
	int	i;

	i = 0;
	while (s[i])
		write(1, &s[i++], 1);
}

char	*tolow(char *s)
{
	int	i;

	i = -1;
	if (!s)
		return (NULL);
	while (s[++i])
		if (s[i] >= 'A' && s[i] <= 'Z')
			s[i] += 32;
	return (s);
}

void	fractal_island(char c, t_prog *prog)
{
	if (c == 'j')
		julia(prog, prog->win);
	if (c == 'm')
		mandelbrot(prog, prog->win);
	if (c == 'b')
		burningship(prog, prog->win);
}

void	p_start(char set, t_var def)
{
	t_prog	prog;

	prog.pos.w = def.w;
	prog.pos.h = def.h;
	prog.pos.zoom = 1;
	prog.pos.movex = 0;
	prog.pos.movey = 0;
	prog.pos.zof = def.zof;
	prog.f.set = set;
	prog.f.color = 0x0009EE10;
	prog.f.cre = def.movex;
	prog.f.cim = def.movey;
	prog.win.mlx = mlx_init();
	prog.win.mlx_win = mlx_new_window(prog.win.mlx, prog.pos.w,
			prog.pos.h, "Fract-ol");
	prog.win.img = mlx_new_image(prog.win.mlx, prog.pos.w,
			prog.pos.h);
	prog.win.addr = mlx_get_data_addr(prog.win.img, &prog.win.bits_per_pixel,
			&prog.win.line_length, &prog.win.endian);
	fractal_island(prog.f.set, &prog);
	mlx_mouse_hook(prog.win.mlx_win, woom, &prog.win);
	mlx_hook(prog.win.mlx_win, 17, 0, end_p, &prog.win);
	mlx_key_hook(prog.win.mlx_win, input, &prog.win);
	mlx_loop(prog.win.mlx);
}

int	main(int ac, char *av[])
{
	t_var	def;

	if (ac < 2 || ac > 7)
		return (putstr(ERROR), 0);
	def.i = 1;
	def.w = 700;
	def.h = 540;
	def.zof = 1;
	if (!ft_strncmp(tolow(av[def.i]), "julia", 5))
	{
		if (defjulia(&def, ac, av, ++def.i))
			p_start('j', def);
	}
	else if (!ft_strncmp(tolow(av[def.i]), "mandelbrot", 10))
	{
		if (define(&def, ac, av, ++def.i))
			p_start('m', def);
	}
	else if (!ft_strncmp(tolow(av[def.i]), "burningship", 11))
	{
		if (define(&def, ac, av, ++def.i))
			p_start('b', def);
	}
	return (putstr(ERROR), 0);
}
