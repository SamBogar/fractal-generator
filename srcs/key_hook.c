/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_hook.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbogar <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/29 15:31:31 by sbogar            #+#    #+#             */
/*   Updated: 2017/06/30 11:37:26 by sbogar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fractol.h"

int				is_first_batch(int keycode, t_mlx **tmp, double imag_per_pixel)
{
	if ((keycode == UP || keycode == DOWN))
	{
		(*tmp)->x_offset += (keycode == DOWN) ?
			-imag_per_pixel : imag_per_pixel;
		draw_window((*tmp));
	}
	else if ((keycode == RIGHT || keycode == LEFT))
	{
		(*tmp)->y_offset += (keycode == RIGHT) ?
			-imag_per_pixel : imag_per_pixel;
		draw_window((*tmp));
	}
	else if (((*tmp)->set == JULIA && keycode == TAB))
	{
		(*tmp)->max_iters = 100;
		(*tmp)->c_real = -0.6775;
		(*tmp)->c_imag = -0.33;
		(*tmp)->zoom = 1.0;
		(*tmp)->x_offset = 0.0;
		(*tmp)->y_offset = 0.0;
		draw_window((*tmp));
	}
	return (0);
}

int				is_second_batch(int keycode, t_mlx **tmp)
{
	int			res;

	res = 0;
	if ((*tmp)->set == MANDLEBROT && keycode == TAB && (res += 1))
	{
		(*tmp)->max_iters = 100;
		(*tmp)->zoom = 1.0;
		(*tmp)->x_offset = 0.0;
		(*tmp)->y_offset = 0.0;
		(*tmp)->color = 1000;
		draw_window((*tmp));
	}
	else if ((*tmp)->set == CUBED && keycode == TAB && (res += 1))
	{
		(*tmp)->max_iters = 100;
		(*tmp)->zoom = 1.0;
		(*tmp)->c_real = 0.39;
		(*tmp)->c_imag = -0.32;
		(*tmp)->x_offset = 0.0;
		(*tmp)->y_offset = 0.0;
		(*tmp)->color = 1000000;
		draw_window((*tmp));
	}
	return (res);
}

int				is_third_batch(int keycode, t_mlx **tmp)
{
	int			res;

	res = 0;
	if (keycode == C && (res += 1))
	{
		(*tmp)->color *= 1.1;
		draw_window((*tmp));
	}
	else if (keycode == V && (res += 1))
	{
		(*tmp)->color /= 0.9;
		draw_window((*tmp));
	}
	else if (keycode == D && (res += 1))
	{
		(*tmp)->color *= 10;
		draw_window((*tmp));
	}
	else if (keycode == F && (res += 1))
	{
		(*tmp)->color /= 10;
		draw_window((*tmp));
	}
	return (res);
}

int				is_fourth_batch(int keycode, t_mlx **tmp)
{
	if (keycode == MINUS)
	{
		(*tmp)->zoom *= 1.1;
		(*tmp)->x_offset *= 1.1;
		(*tmp)->y_offset *= 1.1;
		draw_window((*tmp));
	}
	else if (keycode == PLUS)
	{
		(*tmp)->zoom *= 0.9;
		(*tmp)->x_offset *= 0.9;
		(*tmp)->y_offset *= 0.9;
		draw_window((*tmp));
	}
	else if (keycode == SPACE && ((*tmp)->set == JULIA ||
				(*tmp)->set == CUBED))
		(*tmp)->is_locked = ((*tmp)->is_locked == 1) ? 0 : 1;
	else if ((keycode == LESS_THAN || keycode == GREATER_THAN))
	{
		(*tmp)->max_iters *= (keycode == LESS_THAN) ? 0.9 : 1.1;
		draw_window((*tmp));
	}
	return (0);
}

int				key_hook(int keycode, void *info)
{
	t_mlx		*tmp;
	double		imag_per_pixel;

	tmp = (t_mlx *)info;
	imag_per_pixel = (double)(tmp->zoom / 400.0) * 100;
	if (keycode == ESC)
		exit(0);
	else if (is_first_batch(keycode, &tmp, imag_per_pixel))
		return (0);
	else if (is_second_batch(keycode, &tmp))
		return (0);
	else if (is_third_batch(keycode, &tmp))
		return (0);
	else if (is_fourth_batch(keycode, &tmp))
		return (0);
	return (0);
}
