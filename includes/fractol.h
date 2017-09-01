/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbogar <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/30 10:59:36 by sbogar            #+#    #+#             */
/*   Updated: 2017/06/30 11:39:07 by sbogar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
# define FRACTOL_H

# include "events.h"
# include "../mlx/mlx.h"
# include "../libft/libft.h"
# include <pthread.h>
# include <math.h>

enum				e_sets{
	JULIA,
	MANDLEBROT,
	SIERPINSKI,
	CUBED,
	ERROR
};

enum				e_xy{
	X,
	Y
};

typedef struct		s_iter{
	int				i;
	int				start_x;
	int				end_x;
}					t_iter;

typedef struct		s_mlx{
	void			*win;
	void			*mlx;
	int				w_height;
	int				w_width;

	int				set;
	int				color;

	double			c_real;
	double			c_imag;

	double			zoom;
	double			scales[2];
	double			x_offset;
	double			y_offset;

	int				is_locked;
	int				max_iters;

	void			*image;
	int				*pixels;
	int				bpp;
	int				size;
	int				endian;

	pthread_t		threads[10];
}					t_mlx;

t_mlx				*get_mlx_info(int ac, char **av);
int					motion_hook(int x, int y, void *param);
int					mouse_hook(int button, int x, int y, void *param);
int					get_mandlebrot_color(double s[2], t_mlx *info);
int					recurse(double x, double y, t_mlx *info, double ri[2]);
int					get_sierpinski_color(double x, double y, t_mlx *i);
int					get_julia_color(double s[2], t_mlx *info);
int					get_z_cubed_color(double s[2], t_mlx *info);
int					key_hook(int keycode, void *param);
int					draw_window(t_mlx *info);

#endif
