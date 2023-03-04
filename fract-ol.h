/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fract-ol.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: romaurel <romaurel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/17 22:03:05 by romaurel          #+#    #+#             */
/*   Updated: 2023/03/04 14:53:30 by romaurel         ###   ########.fr       */
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

// KEYS : 
#  define K_UP			65362
#  define K_DOWN		65364
#  define K_LEFT		65361
#  define K_RIGHT		65363

// typedef struct s_img {

// }				t_img;

typedef struct	s_fractal {
	double	cRe;
	double	cIm;
	double	newRe;
	double	newIm;
	double	oldRe;
	double	oldIm;
	int		i;
}				t_fractal;

typedef struct	s_variable {
	double	h;
	double	w;
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
	char	set;
	t_var	c;
}				t_win;

// julia.c
void	julia(t_win img);
int	pixel_farmer(int x, int y, t_win img);


// fract-ol.c
void	p_start(char *set);
void	my_mlx_pixel_put(t_win *data, int x, int y, int color);
int	end_p(t_win img);
int	move(int keycode, t_win *img);

#endif
