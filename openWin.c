#include <unistd.h>
#include <mlx.h>
void ft_putchar(char c)
{
	write(1, &c, 1);
}
int which_key(int key, void *param)
{
	ft_putchar('c');
	return (0);
}

int main()
{
	void	*mlx_ptr;
	void	*win_ptr;
	float		xmin;
	float		ymin;
	float		xMax;
	float		yMax;
	float		rc;
	float		ic;
	float		rz;
	float		iz;
	float		R;
	float		I;
	int			a;

	xmin = -2,5;
	xMax = 2,5;
	ymin = -1,5;
	yMax = 1,5;
	mlx_ptr = mlx_init();
	win_ptr = mlx_new_window(mlx_ptr, 1000, 500, "opWin");
	while (x < 1000)
	{
		while (y < 500)
		{
			rc = xmin + (xMax - xmin)/(1000 * x);
			ic = xmin + (yMax - ymin)/(500 * y);
			rz = 0;
			iz = 0;
			while (a < 15 && (rz*rz + iz*iz) >= 4)
			{
				R = rz;
				
			}
			y++;
		}
	}
		mlx_pixel_put(mlx_ptr, win_ptr, 500, 250, 0xF0FF0F);
	//	mlx_key_hook(win_ptr, which_key, (void *)0);
	mlx_loop(mlx_ptr);
}
