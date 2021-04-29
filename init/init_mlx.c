#include "../headers/cub3d.h"

void	init_mlxdata(t_rc *rc)
{
	rc->mlx = mlx_init();
	rc->win = mlx_new_window(rc->mlx, rc->pars->Rx, rc->pars->Ry, "RayCaster");
	mlx_hook(rc->win, 2, 1L, key_hook, rc);
	mlx_hook(rc->win, 17, 0, ft_close, rc);
	mlx_loop_hook(rc->mlx, key_hook, rc);
	rc->img = mlx_new_image(rc->mlx, rc->pars->Rx, rc->pars->Ry);
	rc->addr = mlx_get_data_addr(rc->img, &rc->bits_per_pixel,
			&rc->line_length, &rc->endian);
}

void	init_mlxntxt(t_rc *rc)
{
	int	i;

	i = 0;
	while (rc->pars->map[i] != NULL)
		i++;
	rc->pars->hmap = i;
	i = 0;
	while (i < 5)
	{
		rc->txtn[i] = wrmalloc(sizeof(t_img));
		i++;
	}
	init_mlxdata(rc);
	load_txtNW(rc);
	load_txtSE(rc);
	load_txtS(rc);
}
