#include <stdio.h>
#include <mlx.h>

typedef struct	s_vars {
	void	*mlx;
	void	*win;
}				t_vars;

int ftclose(int keycode, t_vars *vars)
{
	if (keycode == 53)
		mlx_destroy_window(vars->mlx, vars->win);
	return (0);
}

int mouse_hook(int button,int r, int t, t_vars *stru)
{
	int		xp = 0;
	int		yp = 0;
	int		x = 0;
	int		y = 0;
	double	cRe, cI;
	double	nRe, nIm, oRe, oIm;
	double	zoom = 1, mx = 0, my = 0;
	int		MaxIt = 100;

	mlx_clear_window(((t_vars *)stru)->mlx, ((t_vars *)stru)->win);
	mlx_mouse_get_pos(((t_vars *)stru)->win, &xp, &yp);
	if (button == 5)
	{
		zoom += 2;
		mlx_clear_window(((t_vars *)stru)->mlx, ((t_vars *)stru)->win);
		mlx_mouse_get_pos(((t_vars *)stru)->win, &xp, &yp);
		cRe = -0.75 + ((double)xp/1000)*0.5;
		cI = -0.14 + ((double)yp/500)*0.5;
		while (y < 500)
		{
			while(x < 1000)
			{
				nRe = 1.5 * (x - 1000 / 2) / (0.5 * zoom * 1000) + mx;
				nIm = (y - 500 / 2) / (0.5 * zoom * 500) + my;
				int i = 0;
				while (i < MaxIt && (nRe * nRe + nIm * nIm) <= 4)
				{
					oRe = nRe;
					oIm = nIm;
					nRe = oRe * oRe - oIm * oIm + cRe;
					nIm = 2 * oRe * oIm + cI;
					i++;
				}
				mlx_pixel_put(((t_vars *)stru)->mlx, ((t_vars *)stru)->win, x, y, 0x0101DF * i);
				x++;
			}
			x = 0;
			y++;
		}
	}
	if (button == 4)
	{
		if (zoom > 1)
		{
			zoom -= 1;
			mlx_clear_window(((t_vars *)stru)->mlx, ((t_vars *)stru)->win);
			mlx_mouse_get_pos(((t_vars *)stru)->win, &xp, &yp);
			cRe = -0.75 + ((double)xp/1000)*0.5;
			cI = -0.14 + ((double)yp/500)*0.5;
			while (y < 500)
			{
				while(x < 1000)
				{
					nRe = 1.5 * (x - 1000 / 2) / (0.5 * zoom * 1000) + mx;
					nIm = (y - 500 / 2) / (0.5 * zoom * 500) + my;
					int i = 0;
					while (i < MaxIt && (nRe * nRe + nIm * nIm) <= 4)
					{
						oRe = nRe;
						oIm = nIm;
						nRe = oRe * oRe - oIm * oIm + cRe;
						nIm = 2 * oRe * oIm + cI;
						i++;
					}
					mlx_pixel_put(((t_vars *)stru)->mlx, ((t_vars *)stru)->win, x, y, 0x0101DF * i);
					x++;
				}
				x = 0;
				y++;
			}
		}
	}
	return (0);
}

int render_next_frame(void *stru)
{
	int		xp = 0;
	int		yp = 0;
	int		x = 0;
	int		y = 0;
	double	cRe, cI;
	double	nRe, nIm, oRe, oIm;
	double	zoom = 1, mx = 0, my = 0;
	int		MaxIt = 100; 
	
	mlx_clear_window(((t_vars *)stru)->mlx, ((t_vars *)stru)->win);
	mlx_mouse_get_pos(((t_vars *)stru)->win, &xp, &yp);
	cRe = -0.75 + ((double)xp/1000)*0.5;
	cI = -0.14 + ((double)yp/500)*0.5;
	while (y < 500)
	{
		while(x < 1000)
		{
			nRe = 1.5 * (x - 1000 / 2) / (0.5 * zoom * 1000) + mx;
			nIm = (y - 500 / 2) / (0.5 * zoom * 500) + my;
			int i = 0;
			while (i < MaxIt && (nRe * nRe + nIm * nIm) <= 4)
			{
				oRe = nRe;
				oIm = nIm;
				nRe = oRe * oRe - oIm * oIm + cRe;
				nIm = 2 * oRe * oIm + cI;
				i++;
			}
			mlx_pixel_put(((t_vars *)stru)->mlx, ((t_vars *)stru)->win, x, y, 0x0101DF * i);
			x++;
		}
		x = 0;
		y++;
	}
	return (0);
}

int main()
{
	t_vars	vars;
	vars.mlx = mlx_init();
	vars.win = mlx_new_window(vars.mlx, 1000, 500, "opWin");
	mlx_hook(vars.win, 2, 1L<<0, ftclose, &vars);
	mlx_mouse_hook(vars.win, mouse_hook, &vars);
	mlx_loop_hook(vars.mlx, render_next_frame, (void *)&vars);
	mlx_loop(vars.mlx);
	return (0);
}
