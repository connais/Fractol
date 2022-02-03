/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   firstfract.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avaures <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/03 16:25:53 by avaures           #+#    #+#             */
/*   Updated: 2022/02/03 18:48:25 by avaures          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int	mouse_hook(int button, int o, int y, t_vars *stru)
{
	int	x;

	(void) o;
	(void) y;
	x = 1;
	if (button == 4)
		stru->zoom += x;
	if (button == 5 && stru->zoom > x)
		stru->zoom -= x;
	return (0);
}

void	put_pixel_julia(t_vars *vars, t_coordon coords)
{
	my_mlx_pixel_put(&((t_vars *)vars)->img, coords.x, \
	coords.y, 0x0101DF * coords.incr);
	return ;
}

void	old_new_julia(t_complex *comple)
{
	comple->old_re = comple->new_re;
	comple->old_im = comple->new_im;
	return ;
}

void	calc_fract(double cRe, double cI, t_vars *fract)
{
	t_coordon	coords;
	t_complex	comple;

	coords = make_coor(coords, 0);
	while (coords.y++ < 500)
	{
		while (coords.x++ < 1000)
		{
			comple.new_re = 1.5 * (coords.x - 1000 / 2) / \
			(0.5 * ((t_vars *)fract)->zoom * 1000) + coords.mx;
			comple.new_im = (coords.y - 500 / 2) / \
			(0.5 * ((t_vars *)fract)->zoom * 500) + coords.my;
			coords.incr = 0;
			while (coords.incr++ < coords.max_it && (comple.new_re \
			* comple.new_re + comple.new_im * comple.new_im) <= 4)
			{
				old_new_julia(&comple);
				comple.new_re = comple.old_re * \
				comple.old_re - comple.old_im * comple.old_im + cRe;
				comple.new_im = 2 * comple.old_re * comple.old_im + cI;
			}
			put_pixel_julia(fract, coords);
		}
		coords.x = 0;
	}
	return ;
}

int	render_next_frame(void *stru)
{
	t_coordon	coords;
	static int	xo;
	static int	yo;
	static int	zoom_static;
	double		c_re;
	double		c_im;

	xo = 0;
	yo = 0;
	zoom_static = 0;
	coords = make_coor(coords, 0);
	mlx_mouse_get_pos(((t_vars *)stru)->mlx, \
	((t_vars *)stru)->win, &coords.x_new, &coords.y_new);
	if (zoom_static != ((t_vars *)stru)->zoom || \
	xo != coords.x_new || yo != coords.y_new)
	{
		c_re = 0.285 + ((double)coords.x_new / 1000) * 0.5;
		c_im = 0.01 + ((double)coords.y_new / 500) * 0.5;
		calc_fract(c_re, c_im, stru);
		zoom_static = ((t_vars *)stru)->zoom;
		xo = coords.x_new;
		yo = coords.y_new;
		mlx_put_image_to_window(((t_vars *)stru)->mlx, \
		((t_vars *)stru)->win, ((t_vars *)stru)->img.img, 0, 0);
	}
	return (0);
}

int	main(int argc, char **argv)
{
	t_vars	vars;
	t_data	img;

	if (argc < 2 || (strcmp(argv[1], "MANDELBROT") \
	!= 0 && strcmp(argv[1], "JULIA") != 0))
		write(1, "JULIA\nMANDELBROT", 16);
	else
	{
		vars.mlx = mlx_init();
		vars.win = mlx_new_window(vars.mlx, 1000, 500, argv[1]);
		vars.zoom = 1;
		mlx_hook(vars.win, 2, 1L << 0, ftclose, &vars);
		img.img = mlx_new_image(vars.mlx, 1000, 500);
		mlx_mouse_hook(vars.win, mouse_hook, &vars);
		img.addr = mlx_get_data_addr(img.img, \
		&img.bits_per_pixel, &img.line_length, &img.endian);
		vars.img = img;
		if (strcmp(argv[1], "JULIA") == 0)
			mlx_loop_hook(vars.mlx, render_next_frame, (void *)&vars);
		else
			mlx_loop_hook(vars.mlx, calc_mandel, (void *)&vars);
		mlx_loop(vars.mlx);
	}
	return (0);
}
