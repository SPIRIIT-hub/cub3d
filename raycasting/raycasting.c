#include "../headers/cub3d.h"

void	rc_init(t_rc *rc)
{
	rc->rcd.mapX = (int)(rc->posX);
	rc->rcd.mapY = (int)(rc->posY);
	rc->rcd.sprite = 0;
	rc->deltaDistX = fabs(1 / rc->rayDirX);
	rc->deltaDistY = fabs(1 / rc->rayDirY);
	rc->rcd.hit = 0;
	if (rc->rayDirY == 0)
		rc->deltaDistX = 0;
	else
	{
		if (rc->rayDirX == 0)
			rc->deltaDistX = 1;
		else
			rc->deltaDistX = fabs(1 / rc->rayDirX);
	}
	if (rc->rayDirX == 0)
		rc->deltaDistY = 0;
	else
	{
		if (rc->rayDirY == 0)
			rc->deltaDistY = 1;
		else
			rc->deltaDistY = fabs(1 / rc->rayDirY);
	}
}

void	rc_dir(t_rc *rc)
{
	if (rc->rayDirX < 0)
	{
		rc->rcd.stepX = -1;
		rc->sideDistX = (rc->posX - rc->rcd.mapX) * rc->deltaDistX;
	}
	else
	{
		rc->rcd.stepX = 1;
		rc->sideDistX = (rc->rcd.mapX + 1.0 - rc->posX) * rc->deltaDistX;
	}
	if (rc->rayDirY < 0)
	{
		rc->rcd.stepY = -1;
		rc->sideDistY = (rc->posY - rc->rcd.mapY) * rc->deltaDistY;
	}
	else
	{
		rc->rcd.stepY = 1;
		rc->sideDistY = (rc->rcd.mapY + 1.0 - rc->posY) * rc->deltaDistY;
	}
}

void	send_ray(t_rc *rc)
{
	while (rc->rcd.hit == 0)
	{
		if (rc->sideDistX < rc->sideDistY)
		{
			rc->sideDistX += rc->deltaDistX;
			rc->rcd.mapX += rc->rcd.stepX;
			rc->side = 0;
			rc->sd = 0;
		}
		else
		{
			rc->sideDistY += rc->deltaDistY;
			rc->rcd.mapY += rc->rcd.stepY;
			rc->side = 1;
			rc->sd = 1;
		}
		if (rc->pars->map[rc->rcd.mapX][rc->rcd.mapY] == '1')
			rc->rcd.hit = 1;
	}
}

void	needed_to_draw(t_rc *rc, int x)
{
	if (rc->side == 0)
		rc->rcd.perpWallDist = (rc->rcd.mapX - rc->posX + \
			(1 - rc->rcd.stepX) / 2) / rc->rayDirX;
	else
		rc->rcd.perpWallDist = (rc->rcd.mapY - rc->posY + \
			(1 - rc->rcd.stepY) / 2) / rc->rayDirY;
	rc->rcd.lineHeight = (int)(rc->pars->Ry / rc->rcd.perpWallDist);
	rc->rcd.drawStart = -rc->rcd.lineHeight / 2 + rc->pars->Ry / 2;
	rc->rcd.drawEnd = rc->rcd.lineHeight / 2 + rc->pars->Ry / 2;
	if (rc->side == 0)
	{
		rc->wallX = rc->posY + rc->rcd.perpWallDist * rc->rayDirY;
		if (rc->rayDirX > 0)
			rc->sd = 3;
	}
	else
	{
		rc->wallX = rc->posX + rc->rcd.perpWallDist * rc->rayDirX;
		if (rc->rayDirY > 0)
			rc->sd = 2;
	}
	rc->zBuffer[x] = rc->rcd.perpWallDist;
}

void	ft_Raycaster(t_rc *rc)
{
	int	x;

	x = 0;
	rc->sprindex = -1;
	while (x < rc->pars->Rx)
	{
		rc->cameraX = 2 * x / (double)(rc->pars->Rx) - 1;
		rc->rayDirX = rc->dirX + rc->planeX * rc->cameraX;
		rc->rayDirY = rc->dirY + rc->planeY * rc->cameraX;
		rc_init(rc);
		rc_dir(rc);
		send_ray(rc);
		needed_to_draw(rc, x);
		ft_verLine(x, rc->rcd.drawStart, rc->rcd.drawEnd, rc);
		x++;
	}
	ft_spritedata(rc);
	ft_sprite(rc);
	if (rc->save == 1)
		save_bmp("save.bmp", rc);
	mlx_put_image_to_window(rc->mlx, rc->win, rc->img, 0, 0);
}
