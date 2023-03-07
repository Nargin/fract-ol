/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   others.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: romaurel <romaurel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/05 16:17:49 by romaurel          #+#    #+#             */
/*   Updated: 2023/03/07 18:56:27 by romaurel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fract-ol.h"

void	zero_is_bad(t_prog *prog)
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
		prog->f.color = 0x0009EE10;
}

void	my_mlx_pixel_put(t_win *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

int	key(int k, int l)
{
	return (k == l);
}

double	pardon(double t_, double s_)
{
	return (pow(t_, -s_));
}

double	aad(char *s)
{
	double	g;
	int		i;
	double	n;
	double  c;

	g = 1;
	i = 0;
	n = 0;
	c = 1;
	if (s[i] == '-' || s[i] == '+')
		if (s[i++] == '-')
			g = -1;
	while (s[i] >= '0' && s[i] <= '9')
		n = n * 10 + s[i++] - 48;
	if (s[i] == '.' || s[i] == ',')
		while (s[++i] >= '0' && s[i] <= '9')
			n += (s[i] - 48) * pardon(10, c++);
	return (n * g);
}