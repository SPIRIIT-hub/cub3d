#include "../headers/cub3d.h"

void	ft_spritedata(t_rc *rc)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (i < rc->pars->hmap)
	{
		while (j < rc->pars->lenmax)
		{
			if (rc->pars->map[i][j] == '2')
			{
				rc->sprindex++;
				rc->sprX[rc->sprindex] = i;
				rc->sprX[rc->sprindex + 1] = 0;
				rc->sprY[rc->sprindex] = j;
				rc->sprY[rc->sprindex + 1] = 0;
			}
			j++;
		}
		j = 0;
		i++;
	}
}

void	init_value(t_rc *rc)
{
	rc->spr.spriteX = rc->sprX[rc->spr.order[rc->spr.i]] - rc->posX + 0.5;
	rc->spr.spriteY = rc->sprY[rc->spr.order[rc->spr.i]] - rc->posY + 0.5;
	rc->spr.invDet = 1.0 / (rc->planeX * rc->dirY - rc->dirX * rc->planeY);
	rc->spr.transformX = (rc->spr.invDet * \
		(rc->dirY * rc->spr.spriteX - rc->dirX * rc->spr.spriteY));
	rc->spr.transformY = (rc->spr.invDet * \
		(-rc->planeY * rc->spr.spriteX + rc->planeX * rc->spr.spriteY));
	rc->spr.spriteScreenX = (int)((rc->pars->Rx / 2) * \
		(1 + rc->spr.transformX / rc->spr.transformY));
	rc->spr.spriteHeight = abs((int)(rc->pars->Ry / (rc->spr.transformY)));
	rc->spr.drawStartY = -rc->spr.spriteHeight / 2 + rc->pars->Ry / 2;
	if (rc->spr.drawStartY < 0)
		rc->spr.drawStartY = 0;
	rc->spr.drawEndY = rc->spr.spriteHeight / 2 + rc->pars->Ry / 2;
	if (rc->spr.drawEndY >= rc->pars->Ry)
		rc->spr.drawEndY = rc->pars->Ry - 1;
	rc->spr.spriteWidth = abs((int)(rc->pars->Rx / (rc->spr.transformY)));
	rc->spr.drawStartX = -rc->spr.spriteWidth / 2 + rc->spr.spriteScreenX;
	if (rc->spr.drawStartX < 0)
		rc->spr.drawStartX = 0;
	rc->spr.drawEndX = rc->spr.spriteWidth / 2 + rc->spr.spriteScreenX;
	if (rc->spr.drawEndX >= rc->pars->Rx)
		rc->spr.drawEndX = rc->pars->Rx - 1;
	rc->spr.stripe = rc->spr.drawStartX;
}

void	spr_vertline(t_rc *rc)
{
	rc->spr.y = rc->spr.drawStartY;
	while (rc->spr.y < rc->spr.drawEndY)
	{
		rc->spr.d = (rc->spr.y) * \
			256 - rc->pars->Ry * 128 + rc->spr.spriteHeight * 128;
		rc->spr.texY = ((rc->spr.d * rc->txtn[4]->img_height) / \
			rc->spr.spriteHeight) / 256;
		if (*(unsigned int *)get_pixel(rc->txtn[4],
				rc->spr.texX, rc->spr.texY) != 0)
			my_mlx_pixel_put(rc, rc->spr.stripe, rc->spr.y,
				*(unsigned int *)get_pixel(rc->txtn[4],
					rc->spr.texX, rc->spr.texY));
		rc->spr.y++;
	}
}

void	ft_sprite(t_rc *rc)
{
	ft_sortsprites(rc);
	while (rc->spr.i <= rc->sprindex)
	{
		init_value(rc);
		while (rc->spr.stripe < rc->spr.drawEndX)
		{
			rc->spr.texX = (int)(256 * (rc->spr.stripe - \
				(-rc->spr.spriteWidth / 2 + rc->spr.spriteScreenX)) * \
					rc->txtn[4]->img_width / rc->spr.spriteWidth) / 256;
			if (rc->spr.transformY > 0
				&& rc->spr.stripe > 0
				&& rc->spr.stripe < rc->pars->Rx
				&& rc->spr.transformY < rc->zBuffer[rc->spr.stripe])
			{
				spr_vertline(rc);
			}
			rc->spr.stripe++;
		}
		rc->spr.i++;
	}
}
