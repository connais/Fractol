/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avaures <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/02 11:31:59 by avaures           #+#    #+#             */
/*   Updated: 2022/02/03 18:42:53 by avaures          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
# define FRACTOL_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <string.h>
# include "mlx.h"

typedef struct s_mandel {
	int		x;
	int		y;
	int		max_it;
	int		i;
	double	pr;
	double	pi;
	double	new_re;
	double	new_im;
	double	old_re;
	double	old_im;
	double	mx;
	double	my;
}	t_mandel;

typedef struct s_complex {
	double	new_re;
	double	new_im;
	double	old_re;
	double	old_im;
}	t_complex;

typedef struct s_coordon {
	int		x_new;
	int		y_new;
	int		x;
	int		y;
	int		incr;
	int		max_it;
	double	mx;
	double	my;
}	t_coordon;

typedef struct s_data {
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}	t_data;

typedef struct s_vars {
	void	*mlx;
	void	*win;
	int		zoom;
	t_data	img;
}	t_vars;

int			render_next_frame(void *stru);
int			calc_mandel(void *vars);
int			ftclose(int keycode, t_vars *vars);
int			mouse_hook(int button, int o, int y, t_vars *stru);
void		my_mlx_pixel_put(t_data *data, int x, int y, int color);
void		calc_fract(double cRe, double cI, t_vars *fract);
void		put_pixel_mandel(t_vars *vars, t_mandel mand);
void		put_pixel_julia(t_vars *vars, t_coordon coord);
void		old_new_mandel(t_mandel *mand);
void		old_new_julia(t_complex *comple);
void		exit_game(t_vars *vars);
t_coordon	make_coor(t_coordon coor, int x);
t_mandel	make_mandel(t_mandel mand, int max, double mx, double my);

#endif
