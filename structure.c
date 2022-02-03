/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structure.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avaures <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/02 17:40:09 by avaures           #+#    #+#             */
/*   Updated: 2022/02/03 17:19:31 by avaures          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "fractol.h"

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

t_coordon	make_coor(t_coordon coor, int x)
{
	coor.x_new = x;
	coor.y_new = x;
	coor.x = x;
	coor.y = x;
	coor.my = x;
	coor.mx = x;
	coor.incr = x;
	coor.max_it = 100;
	return (coor);
}

t_mandel	make_mandel(t_mandel mand, int max, double mx, double my)
{
	mand.x = 0;
	mand.y = 0;
	mand.max_it = max;
	mand.mx = mx;
	mand.my = my;
	return (mand);
}

void	exit_game(t_vars *vars)
{
	mlx_destroy_image(vars->mlx, vars->img.img);
	mlx_destroy_window(vars->mlx, vars->win);
	mlx_destroy_display(vars->mlx);
	free(vars->mlx);
	exit(EXIT_SUCCESS);
}

int	ftclose(int keycode, t_vars *vars)
{
	if (keycode == 65307)
		exit_game(vars);
	return (0);
}
