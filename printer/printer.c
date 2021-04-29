#include "headers/cub3d.h"

char	*get_pixel(t_img *data, int x, int y)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	return (dst);
}

void	my_mlx_pixel_put(t_rc *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

void	ft_verLine(int x, int drawstart, int drawend, t_rc *rc)
{
	rc->len = drawend - drawstart;
	rc->wle = 0;
	if (rc->sd == 3 || rc->sd == 1)
		rc->imgx = (rc->txtn[rc->sd]->img_width - 1) - \
			((int)(rc->txtn[rc->sd]->img_width * \
				(rc->wallX - (int)rc->wallX)));
	else
		rc->imgx = (int)(rc->txtn[rc->sd]->img_width * \
			(rc->wallX - (int)rc->wallX));
	rc->imgy = (int)(((rc->txtn[rc->sd]->img_height - 1) / \
		(double)rc->len) * rc->wle);
	while (rc->wle < drawstart)
	{
		my_mlx_pixel_put(rc, x, rc->wle, ((rc->pars->C_R << 16) | \
			((rc->pars->C_G << 8) | rc->pars->C_B)));
		rc->wle++;
	}
	prnt_txt(x, drawstart, drawend, rc);
	while (rc->wle < rc->pars->Ry)
	{
		my_mlx_pixel_put(rc, x, rc->wle, ((rc->pars->F_R << 16) | \
			((rc->pars->F_G << 8) | rc->pars->F_B)));
		rc->wle++;
	}
}

void	prnt_txt(int x, int drawstart, int drawend, t_rc *rc)
{
	rc->wle = 0;
	while (rc->wle < rc->len)
	{
		rc->imgy = (int)((((rc->txtn[rc->sd]->img_height - 1)) / \
			(double)rc->len) * rc->wle);
		if (drawstart > 0 && !(drawstart >= rc->pars->Ry))
			my_mlx_pixel_put(rc, x, drawstart,
				*(unsigned int *)get_pixel(rc->txtn[rc->sd],
					rc->imgx, rc->imgy));
		rc->wle++;
		drawstart++;
	}
	rc->wle = drawend;
}
