/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fract-ol.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: romaurel <romaurel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/17 22:03:05 by romaurel          #+#    #+#             */
/*   Updated: 2023/03/03 15:20:11 by robin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACT_OL_H
# define FRACT_OL_H

# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <string.h>
# include <math.h>
# include <mlx.h>

typedef struct	s_variable {
	double	h;
	double	w;
	double	cRe;
	double	cIm;
	double	newRe;
	double	newIm;
	double	oldRe;
	double	oldIm;
	double	zoom;
	double	moveX;
	double	moveY;
}				t_var;

typedef struct	s_window {
	void	*mlx;
	void	*mlx_win;
	void	*img;
	void	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
	t_var	c;
}				t_win;

// julia.c
void	julia(t_win img);
int	pixel_farmer(int x, int y, t_var c);


// fract-ol.c
void	p_start(char *set);
void	my_mlx_pixel_put(t_win *data, int x, int y, int color);

#endif
