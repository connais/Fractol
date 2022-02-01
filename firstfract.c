#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include"mlx.h"
typedef struct	t_coordon{
	int		x_new;
	int		y_new;
	int		x;
	int		y;
	int		mx;
	int		my;
}	s_coordon;

typedef struct	s_data {
	void		*img;
	char		*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}				t_data;
typedef struct	s_vars {
	void	*mlx;
	void	*win;
	int	zoom;
	t_data 	img;	
}				t_vars;

s_coordon make_coor(s_coordon coor, int x)
{
	coor.x_new = x;
	coor.y_new = x;
	coor.x = x;
	coor.y = x;
	coor.my = x;
	coor.mx = x;
	return (coor);
}
int ftclose(int keycode, t_vars *vars)
{
	if (keycode == 53)
		mlx_destroy_window(vars->mlx, vars->win);
	return (0);
}

int mouse_hook(int button, int o, int y, t_vars *stru)
{
	int x;

	(void)o;
	(void)y;
	x = 1;
	if (button == 4)
		stru->zoom += x;
	if (button == 5 && stru->zoom > x)
		stru->zoom -= x;
	return (0);
}

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

int render_next_frame(void *stru)
{
	s_coordon	coords;
	coords = make_coor(coords, 0);
	int static	xo = 0;
	int static 	yo = 0;
//	int 		xn = 0;
//	int 		yn = 0;
//	int		x = 0;
//	int		y = 0;
	double	cRe, cI;
	double	nRe, nIm, oRe, oIm;
	double	mx = 0, my = 0;
	int		MaxIt = 100; 
	int static	zoom_static = 0;
	
	mlx_mouse_get_pos(((t_vars *)stru)->mlx , ((t_vars *)stru)->win, &coords.x_new, &coords.y_new);	
	if (zoom_static != ((t_vars *)stru)->zoom || xo != coords.x_new || yo != coords.y_new)
	{
		cRe = 0.285 + ((double)coords.x_new/1000)*0.5;
		cI = 0.01 + ((double)coords.y_new/500)*0.5;
		while (coords.y < 500)
		{
			while(coords.x < 1000)
			{
				nRe = 1.5 * (coords.x - 1000 / 2) / (0.5 * ((t_vars *)stru)->zoom * 1000) + mx;
				nIm = (coords.y - 500 / 2) / (0.5 * ((t_vars *)stru)->zoom * 500) + my;
				int i = 0;
				while (i < MaxIt && (nRe * nRe + nIm * nIm) <= 4)
				{
					oRe = nRe;
					oIm = nIm;
					nRe = oRe * oRe - oIm * oIm + cRe;
					nIm = 2 * oRe * oIm + cI;
					i++;
				}
				my_mlx_pixel_put(&((t_vars *)stru)->img, coords.x, coords.y, 0x0101DF * i);
				coords.x++;
			}
			coords.x = 0;
			coords.y++;
		}
	
		zoom_static = ((t_vars *)stru)->zoom;
		xo = coords.x_new;
		yo = coords.y_new;
		mlx_put_image_to_window(((t_vars *)stru)->mlx,((t_vars *)stru)->win, ((t_vars *)stru)->img.img, 200, 200);
	}
	return (0);
}

int main(int argc, char **argv)
{
	printf("%d", argc);
	if (argc < 2 || strcmp(argv[1], "MANDELBROT") != 0 && strcmp(argv[1], "JULIA") != 0)
	{
		write(1, "JULIA", 5);
		write(1, "\n", 1);
		write(1, "MANDELBROT", 10);
		return (0);
	}
	else 
	{
		t_vars	vars;
		t_data	img;
		vars.mlx = mlx_init();
		vars.win = mlx_new_window(vars.mlx, 2000, 1000, "opWin");
		vars.zoom = 1;
		mlx_hook(vars.win, 2, 1L<<0, ftclose, &vars);
		img.img = mlx_new_image(vars.mlx, 1000, 500);
		mlx_mouse_hook(vars.win, mouse_hook, &vars);
		img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length, &img.endian);
		vars.img = img;
		mlx_loop_hook(vars.mlx, render_next_frame, (void *)&vars);
		mlx_loop(vars.mlx);
	}
	return (0);
}
