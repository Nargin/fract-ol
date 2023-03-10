/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fract-ol.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: romaurel <romaurel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/17 22:03:05 by romaurel          #+#    #+#             */
/*   Updated: 2023/03/10 19:46:54 by romaurel         ###   ########.fr       */
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

# ifndef MAX
#  define MAX 128
# endif

// KEYS : 
#  define K_UP			65362
#  define K_DOWN		65364
#  define K_LEFT		65361
#  define K_RIGHT		65363
#  define ESC			65307
#  define Z				122
#  define R				114
#  define Q				113
#  define D				100
#  define C				99
#  define A				97
#  define ZM			5
#  define ZP			4

// Structure : 
typedef struct	s_fractal {
	double	cRe;
	double	cIm;
	double	newRe;
	double	newIm;
	double	oldRe;
	double	oldIm;
	double	temp;
	char	set;
	int		color;
}				t_fractal;

typedef struct	s_variable {
	long double	zoom;
	long double	moveX;
	long double	moveY;
	long double	tempX;
	long double tempY;
	double	w;
	double	h;
}				t_var;

typedef struct s_win {
	void	*mlx;
	void	*mlx_win;
	void	*img;
	void	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}				t_win;

// Main struct
typedef struct	s_prog {
	t_win	win;
	t_var	pos;
	t_fractal	f;
}				t_prog;


/*			Prototype			*/

// julia.c
int		ft_strncmp(const char *s1, const char *s2, size_t n);
int		pixel_farmer(int x, int y, t_prog *prog);
void	julia(t_prog *prog, t_win win);

// mandelbrot.c
int		pixelitito(int x, int y, t_prog *prog);
void	mandelbrot(t_prog *prog, t_win win);

// burningship.c
int sea_of_pixels(int x, int y, t_prog *prog);
void    burningship(t_prog *prog, t_win win);

// input.c
int		woom(int keycode, int x, int y, t_prog *prog);
void	change_reality(int keycode, t_prog *prog);
int		input(int keycode, t_prog *prog);
int		move(int keycode, t_prog *img);
int		end_p(t_prog *prog);

// others.c
void	my_mlx_pixel_put(t_win *data, int x, int y, int color);
double 	pardon(double t_, double s_);
void	zero_is_bad(t_prog *prog);
int		key(int k, int l);
double	aad(char *s);

// fract-ol.c
void	fractal_island(char c, t_prog *prog);
void	p_start(char set);

#endif
