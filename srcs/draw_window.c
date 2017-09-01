/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_window.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbogar <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/21 13:21:51 by sbogar            #+#    #+#             */
/*   Updated: 2017/06/30 13:49:53 by sbogar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fractol.h"

static int		get_color(t_mlx *info, double scales[2], int x, int y)
{
	if (info->set == JULIA || info->set == MANDLEBROT)
		return ((info->set == JULIA) ?
			get_julia_color(scales, info) : get_mandlebrot_color(scales, info));
	else if (info->set == SIERPINSKI)
		return (get_sierpinski_color(x, y, info));
	else if (info->set == CUBED)
		return (get_z_cubed_color(scales, info));
	return (0);
}

static void		*print(t_mlx *info, int x, int end_x, int i)
{
	int			y;
	double		scales[2];
	double		tmp_scale;

	tmp_scale = info->zoom / 400.0;
	scales[X] = tmp_scale * x - info->zoom;
	while (x < end_x)
	{
		y = 0;
		scales[Y] = -info->zoom;
		while (y < 800)
		{
			info->pixels[i] = get_color(info, scales, x, y);
			y++;
			i++;
			scales[Y] += tmp_scale;
		}
		scales[X] += tmp_scale;
		x++;
	}
	return (NULL);
}

void			*get_print_params(void *info)
{
	t_mlx		*param;
	int			i;

	i = -1;
	param = (t_mlx*)info;
	while (++i <= 9)
		if (pthread_equal(pthread_self(), (param->threads)[i]))
			print(param, i * 80, (i + 1) * 80, i * 80 * 800);
	return (NULL);
}

int				draw_window(t_mlx *info)
{
	int			i;

	i = 0;
	mlx_clear_window(info->mlx, info->win);
	while (i <= 9)
		pthread_create(&(info->threads)[i++], NULL,
				get_print_params, (void*)info);
	while (i - 9 <= 9)
		pthread_join((info->threads)[(i++ - 9)], NULL);
	mlx_put_image_to_window(info->mlx, info->win, info->image, 0, 0);
	return (0);
}
