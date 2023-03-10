/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   julia.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: romaurel <romaurel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/03 22:01:17 by robin             #+#    #+#             */
/*   Updated: 2023/03/10 19:45:03 by romaurel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fract-ol.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	int	i;

	i = 0;
	while (((char *)s1)[i] && ((char *)s1)[i] == ((char *)s2)[i] && n--)
		i++;
	if (!n)
		return (0);
	return (((unsigned char *)s1)[i] - ((unsigned char *)s2)[i]);
}

int	pixel_farmer(int x, int y, t_prog *prog)
{
	int			i;
	t_fractal	f;

	i = -1;
	f.newRe = 1.5 * (x - prog->pos.w / 2) / (0.5 * prog->pos.zoom * prog->pos.w) + prog->pos.moveX;
	f.newIm = (y - prog->pos.h / 2) / (0.5 * prog->pos.zoom * prog->pos.h) + prog->pos.moveY;
	while(++i < 128 && (f.newRe * f.newRe + f.newIm * f.newIm) <= 4)
	{
		//remember value of previous iteration
		f.oldRe = f.newRe;
		f.oldIm = f.newIm;
		//the actual iteration, the real and imaginary part are calculated
		f.newRe = f.oldRe * f.oldRe - f.oldIm * f.oldIm + prog->f.cRe;
		f.newIm = 2 * f.oldRe * f.oldIm + prog->f.cIm;
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
