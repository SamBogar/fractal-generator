/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbogar <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/19 22:53:45 by sbogar            #+#    #+#             */
/*   Updated: 2017/06/30 15:44:14 by sbogar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fractol.h"

int			get_set(int ac, char **av)
{
	if (ac == 2)
	{
		if (!ft_strcmp(av[1], "julia"))
			return (JULIA);
		else if (!ft_strcmp(av[1], "mandlebrot"))
			return (MANDLEBROT);
		else if (!ft_strcmp(av[1], "sierpinski"))
			return (SIERPINSKI);
		else if (!ft_strcmp(av[1], "cubed"))
			return (CUBED);
	}
	return (ERROR);
}

void		get_mlx_stuff(t_mlx *info, char **av)
{
	info->mlx = mlx_init();
	info->w_height = 800;
	info->w_width = 800;
	info->win = mlx_new_window(info->mlx, info->w_height,
				info->w_width, av[1]);
	info->image = mlx_new_image(info->mlx, info->w_width, info->w_height);
	info->pixels = (int *)mlx_get_data_addr(info->image, &info->bpp,
					&info->size, &info->endian);
}

t_mlx		*get_env_info(int ac, char **av)
{
	t_mlx	*info;

	info = (t_mlx*)malloc(sizeof(t_mlx));
	info->set = get_set(ac, av);
	if (info->set == ERROR)
		return (0);
	info->c_real = (info->set == JULIA) ? -0.695 : 0.39;
	info->c_imag = (info->set == JULIA) ? 0.4725 : -0.32;
	info->color = (info->set == JULIA) ? 1000 : 1000000;
	if (info->set == MANDLEBROT)
		info->color = 32767;
	info->zoom = 1.0;
	info->max_iters = 100;
	info->x_offset = 0.0;
	info->y_offset = 0.0;
	info->scales[X] = 0.0;
	info->scales[Y] = 0.0;
	info->is_locked = 0;
	get_mlx_stuff(info, av);
	return (info);
}

int			main(int ac, char **av)
{
	t_mlx	*info;

	info = get_env_info(ac, av);
	if (!info)
	{
		ft_putstr("Available options:\n\tmandlebrot\n\tjulia\n\tcubed\n");
		return (0);
	}
	draw_window(info);
	mlx_key_hook(info->win, key_hook, info);
	mlx_hook(info->win, 6, 0, motion_hook, info);
	mlx_mouse_hook(info->win, mouse_hook, info);
	mlx_expose_hook(info->win, draw_window, info);
	mlx_loop(info->mlx);
	return (0);
}
