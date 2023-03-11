/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   julia.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: romaurel <romaurel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/03 22:01:17 by robin             #+#    #+#             */
/*   Updated: 2023/03/11 12:05:12 by romaurel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int	ft_strncmp(char *s1, char *s2, size_t n)
{
	int	i;

	i = 0;
	while (((char *)s1)[i] && ((char *)s1)[i] == ((char *)s2)[i] && n--)
		i++;
	if (!n)
		return (0);
	return (((char *)s1)[i] - ((char *)s2)[i]);
}

int	pixel_farmer(int x, int y, t_prog *prog)
{
	int			i;
	t_fractal	f;

	i = -1;
	f.newre = 1.5 * (x - prog->pos.w / 2) / (0.5 * prog->pos.zoom * prog->pos.w)
		+ prog->pos.movex;
	f.newim = (y - prog->pos.h / 2) / (0.5 * prog->pos.zoom * prog->pos.h)
		+ prog->pos.movey;
	while (++i < 128 && (f.newre * f.newre + f.newim * f.newim) <= 4)
	{
		f.oldre = f.newre;
		f.oldim = f.newim;
		f.newre = f.oldre * f.oldre - f.oldim * f.oldim + prog->f.cre;
		f.newim = 2 * f.oldre * f.oldim + prog->f.cim;
	}
	return (i);
}

void	julia(t_prog *prog, t_win win)
{
	int		x;
	int		y;
	int		i;

	y = -1;
	while (++y < prog->pos.h)
	{
		x = -1;
		while (++x < prog->pos.w)
		{
			i = pixel_farmer(x, y, prog);
			if (i == MAX)
				my_mlx_pixel_put(&win, x, y, 0);
			else
				my_mlx_pixel_put(&win, x, y, prog->f.color * i);
		}
	}
}
