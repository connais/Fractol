#include <stdio.h>
#include <mlx.h>
int main()
{
	int		x = 0;
	int		y = 0;
	double	pr, pi;
	double	nRe, nIm, oRe, oIm;
	double	zoom = 1, mx = 0, my = 0;
	int		MaxIt = 5000; 
	void		*mlx_ptr;
	void		*win_ptr;
	
	mlx_ptr = mlx_init();
	win_ptr = mlx_new_window(mlx_ptr, 1000, 500, "opWin");
	//mlx_pixel_put(mlx_ptr, win_ptr, 500, 250, 0xF0FF0F);
	while (y < 500)
	{
		while(x < 1000)
		{
			pr = 1.0 * (x - 1000 / 2) / (0.5 * zoom * 1000) + mx;
			pi = (y - 500 / 2) / (0.5 * zoom * 500) + my;
			nRe = nIm = oRe = oIm = 0;
			int i = 0;
			while (i < MaxIt && (nRe * nRe + nIm * nIm) <= 4)
			{
				oRe = nRe;
				oIm = nIm;
				nRe = oRe * oRe - oIm * oIm + pr;
				nIm = 2 * oRe * oIm + pi;
				i++;
			}
			mlx_pixel_put(mlx_ptr, win_ptr, x, y, 0x8D33FF * i);
			x++;
		}
		x = 0;
		y++;
	}
	//	mlx_key_hook(win_ptr, which_key, (void *)0);
	mlx_loop(mlx_ptr);
	return (0);
}
