/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_color.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbogar <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/19 21:40:09 by sbogar            #+#    #+#             */
/*   Updated: 2017/07/02 16:24:28 by sbogar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fractol.h"

int			recurse(double x, double y, t_mlx *info, double ri[2])
{
	int		i;
	double	tmp_y;
	double	tmp_x;

	i = 0;
	while (i <= info->max_iters)
	{
		tmp_x = (x * x) - (y * y) + ri[X];
		tmp_y = 2 * (x * y) + ri[Y];
		if ((tmp_x * tmp_x) + (tmp_y * tmp_y) > 4)
			return (i * info->color);
		i++;
		x = tmp_x;
		y = tmp_y;
	}
	return (0);
}

int			get_julia_color(double scales[2], t_mlx *info)
{
	double	tmp_y;
	double	tmp_x;
	double	ri[2];

	tmp_y = scales[Y] - info->y_offset;
	tmp_x = scales[X] - info->x_offset;
	ri[X] = info->c_real;
	ri[Y] = info->c_imag;
	return (recurse(tmp_x, tmp_y, info, ri));
}

int			get_mandlebrot_color(double scales[2], t_mlx *info)
{
	double	ri[2];

	ri[X] = scales[Y] - info->y_offset;
	ri[Y] = scales[X] - info->x_offset;
	return (recurse(0, 0, info, ri));
}

int			get_z_cubed_color(double scales[2], t_mlx *info)
{
	int		i;
	double	xy[2];
	double	tmp_y;
	double	tmp_x;
	double	ri[2];

	i = 0;
	ri[X] = info->c_real;
	ri[Y] = info->c_imag;
	xy[X] = scales[X] - info->x_offset;
	xy[Y] = scales[Y] - info->y_offset;
	while (i <= info->max_iters)
	{
		tmp_x = (xy[X] * xy[X] * xy[X]) - (3 * xy[X] * xy[Y] * xy[Y]) + ri[X];
		tmp_y = (3 * xy[X] * xy[X] * xy[Y]) + (xy[Y] * xy[Y] * xy[Y]) + ri[Y];
		if ((tmp_x * tmp_x) + (tmp_y * tmp_y) > 4)
			return (i * info->color);
		i++;
		xy[X] = tmp_x;
		xy[Y] = tmp_y;
	}
	return (0);
}

int			get_sierpinski_color(double x, double y, t_mlx *info)
{
	int		i;

	i = 0;
	x *= info->zoom;
	y *= info->zoom;
	while (x > 0 && y > 0 && i < 100)
	{
		if ((int)x % 3 == 1 && (int)y % 3 == 1)
			return (0);
		x /= 3.0;
		y /= 3.0;
		i++;
	}
	return (i * info->color);
}
