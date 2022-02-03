/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Mandel.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avaures <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/03 13:19:40 by avaures           #+#    #+#             */
/*   Updated: 2022/02/03 18:40:49 by avaures          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "fractol.h"

t_mandel	init_mandel(t_mandel mand)
{
	mand.new_re = 0;
	mand.new_im = 0;
	mand.old_re = 0;
	mand.old_im = 0;
	mand.i = 0;
	return (mand);
}

void	put_pixel_mandel(t_vars *vars, t_mandel mand)
{
	my_mlx_pixel_put(&((t_vars *)vars)->img, \
	mand.x, mand.y, 0x0101DF * mand.i);
	return ;
}

void	old_new_mandel(t_mandel *mand)
{
	mand->old_re = mand->new_re;
	mand->old_im = mand->new_im;
	return ;
}

void	draw_mandel(t_vars *vars)
{
	t_mandel	mand;

	mand = make_mandel(mand, 500, -0.74364, 0.13182);
	while (mand.y++ < 500)
	{
		while (mand.x++ < 1000)
		{
			mand.pr = 1.5 * (mand.x - 1000 / 2) / \
			(0.5 * ((t_vars *)vars)->zoom * 1000) + mand.mx;
			mand.pi = (mand.y - 500 / 2) / \
			(0.5 * ((t_vars *)vars)->zoom * 500) + mand.my;
			mand = init_mandel(mand);
			while (mand.i++ < mand.max_it && (mand.new_re * mand.new_re \
			+ mand.new_im * mand.new_im) <= 4)
			{
				old_new_mandel(&mand);
				mand.new_re = mand.old_re * mand.old_re - mand.old_im \
				* mand.old_im + mand.pr;
				mand.new_im = 2 * mand.old_re * mand.old_im + mand.pi;
			}
			put_pixel_mandel(vars, mand);
		}
		mand.x = 0;
	}
	return ;
}

int	calc_mandel(void *vars)
{
	static int	zoom_static;

	zoom_static = 0;
	if (zoom_static != ((t_vars *)vars)->zoom)
	{
		draw_mandel(vars);
		zoom_static = ((t_vars *)vars)->zoom;
		mlx_put_image_to_window(((t_vars *)vars)->mlx, \
		((t_vars *)vars)->win, ((t_vars *)vars)->img.img, 0, 0);
	}
	return (0);
}
/*
int main()
{
	t_vars vars;
	vars.mlx = mlx_init();
	vars.win = mlx_new_window(vars.mlx, 1000, 500, "opWin");
	mlx_loop_hook(vars.mlx, calc_mandel, (void *)&vars);
	mlx_loop(vars.mlx);
	return (0);
}*/
