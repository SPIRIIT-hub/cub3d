#include "../headers/cub3d.h"

void	load_txtNW(t_rc *rc)
{
	rc->txtn[0]->img = mlx_png_file_to_image(rc->mlx,
			rc->pars->pathtoNO, &rc->txtn[0]->img_width,
			&rc->txtn[0]->img_height);
	if (!(rc->txtn[0]->img))
	{
		printf("Error, North texture not found\n");
		wrdestroy();
		exit(0);
	}
	rc->txtn[0]->addr = mlx_get_data_addr(rc->txtn[0]->img,
			&rc->txtn[0]->bits_per_pixel, &rc->txtn[0]->line_length,
			&rc->txtn[0]->endian);
	rc->txtn[1]->img = mlx_png_file_to_image(rc->mlx,
			rc->pars->pathtoWE, &rc->txtn[1]->img_width,
			&rc->txtn[1]->img_height);
	if (!(rc->txtn[1]->img))
	{
		printf("Error, West texture not found\n");
		wrdestroy();
		exit(0);
	}
	rc->txtn[1]->addr = mlx_get_data_addr(rc->txtn[1]->img,
			&rc->txtn[1]->bits_per_pixel, &rc->txtn[1]->line_length,
			&rc->txtn[1]->endian);
}

void	load_txtSE(t_rc *rc)
{
	rc->txtn[2]->img = mlx_png_file_to_image(rc->mlx,
			rc->pars->pathtoEA, &rc->txtn[2]->img_width,
			&rc->txtn[2]->img_height);
	if (!(rc->txtn[2]->img))
	{
		printf("Error, East texture not found\n");
		wrdestroy();
		exit(0);
	}
	rc->txtn[2]->addr = mlx_get_data_addr(rc->txtn[2]->img,
			&rc->txtn[2]->bits_per_pixel, &rc->txtn[2]->line_length,
			&rc->txtn[2]->endian);
	rc->txtn[3]->img = mlx_png_file_to_image(rc->mlx,
			rc->pars->pathtoSO, &rc->txtn[3]->img_width,
			&rc->txtn[3]->img_height);
	if (!(rc->txtn[3]->img))
	{
		printf("Error, South texture not found\n");
		wrdestroy();
		exit(0);
	}
	rc->txtn[3]->addr = mlx_get_data_addr(rc->txtn[3]->img,
			&rc->txtn[3]->bits_per_pixel, &rc->txtn[3]->line_length,
			&rc->txtn[3]->endian);
}

void	load_txtS(t_rc *rc)
{
	rc->txtn[4]->img = mlx_png_file_to_image(rc->mlx,
			rc->pars->pathtoS, &rc->txtn[4]->img_width,
			&rc->txtn[4]->img_height);
	if (!(rc->txtn[4]->img))
	{
		printf("Error, Sprite texture not found\n");
		wrdestroy();
		exit(0);
	}
	rc->txtn[4]->addr = mlx_get_data_addr(rc->txtn[4]->img,
			&rc->txtn[4]->bits_per_pixel, &rc->txtn[4]->line_length,
			&rc->txtn[4]->endian);
}
