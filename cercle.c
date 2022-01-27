#include <stdio.h>
#include <unistd.h>
#include <mlx.h>

typedef struct	s_vars {
	void	*mlx;
	void	*win;
}				t_vars;

void carre(int x, int y, t_vars *vars)
{
	int i, j;

	i = 0; 
	j = 0;
	while(j <= 10)
	{
		while (i <= 10)
		{
			mlx_pixel_put(vars->mlx, vars->win, x + i, y, 0xF0FF0F);
			i++;
		}
		i = 0;
		j++;
	}
	return;
}


int	ftclose(int keycode, t_vars *vars)
{
	if (keycode == 53)
		mlx_destroy_window(vars->mlx, vars->win);
	return (0);
}

int mouse_hook(int button,int r, int t, t_vars *vars)
{
	int 	x = 0;
	int		xp = 500;
	int 	y = 0;
	int		yp = 250;
	int 	rayon = 100;
	int		test;
	
	if (button == 5)
	{
		while (y < 500)
		{
			while(x < 1000)
			{
				test = (x*x -2*x*xp  + xp*xp) + (y*y -2*y*yp + yp*yp);
				if (test <= rayon*rayon && test >= rayon*rayon - rayon - rayon)
					carre(x, y, vars);
				x++;
			}
			x = 0;
			y++;
		}
	}
	return (0);
}

int	render_next_frame(void *stru)
{
	int 	x = 0;
	int		xp = 500;
	int 	y = 0;
	int		yp = 250;
	int 	rayon = 100;
	int		test;
	
	mlx_clear_window(((t_vars *)stru)->mlx, ((t_vars *)stru)->win);
	mlx_mouse_get_pos(((t_vars *)stru)->win, &xp, &yp);
	//mlx_mouse_hook(((t_vars *)stru)->win, mouse_hook, &stru);
	while (y < 500)
	{
		while(x < 1000)
		{
			test = (x*x -2*x*xp  + xp*xp) + (y*y -2*y*yp + yp*yp);
			if (test <= rayon*rayon && test >= rayon*rayon - rayon - rayon)
				mlx_pixel_put(((t_vars *)stru)->mlx, ((t_vars *)stru)->win, x, y, 0xF0FF0F * x);
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
