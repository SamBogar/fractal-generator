/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbogar <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/19 22:09:36 by sbogar            #+#    #+#             */
/*   Updated: 2017/06/30 11:37:00 by sbogar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fractol.h"

int				motion_hook(int x, int y, void *param)
{
	t_mlx		*tmp;

	tmp = (t_mlx *)param;
	if ((tmp->set == CUBED || tmp->set == JULIA) && !tmp->is_locked)
	{
		tmp->c_real = (double)x * (double)(tmp->zoom / 400.0) - tmp->x_offset;
		tmp->c_imag = (double)y * (double)(tmp->zoom / 400.0) - tmp->y_offset;
		draw_window(tmp);
	}
	return (0);
}

int				mouse_hook(int button, int x, int y, void *info)
{
	t_mlx		*tmp;
	double		idfk;
	double		new_ri[2];
	double		old_ri[2];

	idfk = -1.0;
	tmp = (t_mlx *)info;
	old_ri[X] = (tmp->zoom / 400.0) * x - tmp->zoom;
	old_ri[Y] = (tmp->zoom / 400.0) * y - tmp->zoom;
	if (button == WHEEL_UP || button == WHEEL_DOWN)
	{
		tmp->zoom *= (button == WHEEL_UP) ? 0.9 : 1.1;
		new_ri[X] = (tmp->zoom / 400.0) * x - tmp->zoom;
		new_ri[Y] = (tmp->zoom / 400.0) * y - tmp->zoom;
		if (!((x < 400 && y < 400) || (x > 400 && y > 400)))
			idfk = 1.0;
		tmp->x_offset += (button == WHEEL_UP) ?
			idfk * (old_ri[X] - new_ri[X]) : idfk * -(old_ri[X] - new_ri[X]);
		tmp->y_offset += (button == WHEEL_UP) ?
			idfk * (old_ri[Y] - new_ri[Y]) : idfk * -(old_ri[Y] - new_ri[Y]);
	}
	draw_window(tmp);
	return (0);
}
