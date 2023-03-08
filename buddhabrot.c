/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buddhabrot.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: romaurel <romaurel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/08 17:11:29 by romaurel          #+#    #+#             */
/*   Updated: 2023/03/08 22:01:35 by romaurel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fract-ol.h"

// int	full_w_superior(int x, int y)
// {
// 	int			itermax;
// 	int			i;
// 	t_fractal	f;

// 	f.newRe = 0; // xtemp
// 	f.newIm = 0; // ytemp
// 	itermax = 10000;
// 	i = -1;
// 	while (f.newRe * f.newRe + f.newIm * f.newIm < 4 && ++i < itermax)
// 	{
// 		f.oldRe = f.newRe * f.newRe - f.newIm * f.newIm + x;
// 		f.newIm = 2 * f.newRe * f.newIm + y;
// 		f.newRe = f.oldRe;
// 	}
// 	printf("%d\n", i);
// 	return (i);
// }

// void	buddhabrot(t_prog *prog, t_win win)
// {
// 	int		x;
// 	int		y;
// 	int		i;

// 	y = -1;
// 	while (++y < prog->pos.h)
// 	{
// 		x = -1;
// 		while (++x < prog->pos.w)
// 		{
// 			i = full_w_superior(x, y);
// 			if (i > 50 && i < 10000)
// 				my_mlx_pixel_put(&win, x, y, 0);
// 			else
// 				my_mlx_pixel_put(&win, x, y, prog->f.color);
// 		}
// 	}
// }


void    buddhabrot(t_prog *prog, t_win win)
{
    double  c_re;
    double  c_im;
    double  x;
    double  y;
    double  x_new;
    double  y_new;
    int     i;
    int     j;
    int     k;
    int     l;

    i = -1;
    while (++i < prog->pos.w)
    {
        j = -1;
        while (++j < prog->pos.h)
        {
            c_re = (i - prog->pos.w / 2.0) * 4.0 / prog->pos.w / prog->pos.zoom + prog->pos.moveX;
            c_im = (j - prog->pos.h / 2.0) * 4.0 / prog->pos.h / prog->pos.zoom + prog->pos.moveY;
            x = 0;
            y = 0;
            k = -1;
            while (++k < 50000)
            {
                x_new = x * x - y * y + c_re;
                y_new = 2 * x * y + c_im;
                x = x_new;
                y = y_new;
                if (x * x + y * y > 4)
                    break ;
                if (k > MAX)
                    break ;
            }
            if (k >= MAX)
            {
                x = 0;
                y = 0;
                k = -1;
                while (++k < 500)
                {
                    x_new = x * x - y * y + c_re;
                    y_new = 2 * x * y + c_im;
                    x = x_new;
                    y = y_new;
                    if (x * x + y * y > 4)
                        break ;
                    l = -1;
                    while (++l < k)
                    {
                        x_new = x * x - y * y + c_re;
                        y_new = 2 * x * y + c_im;
                        x = x_new;
                        y = y_new;
                        if (x * x + y * y > 4)
                            break ;
                        my_mlx_pixel_put(&win, (x_new - prog->pos.moveX) * prog->pos.w / 4.0 / prog->pos.zoom + prog->pos.w / 2.0,
                                    (y_new - prog->pos.moveY) * prog->pos.h / 4.0 / prog->pos.zoom + prog->pos.h / 2.0, 0xFFFFFF);
                    }
                }
            }
        }
    }
}