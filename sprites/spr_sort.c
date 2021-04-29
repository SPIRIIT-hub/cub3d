#include "../headers/cub3d.h"

void	init_sort(t_rc *rc)
{
	rc->spr.i = 0;
	while (rc->spr.i <= rc->sprindex)
	{
		rc->spr.spriteDistance[rc->spr.i] = ((rc->posX - rc->sprX[rc->spr.i]) * \
			(rc->posX - rc->sprX[rc->spr.i]) + (rc->posY - rc->sprY[rc->spr.i]) * \
				(rc->posY - rc->sprY[rc->spr.i]));
		rc->spr.i++;
	}
	rc->spr.i = 0;
	rc->spr.tmp = 0;
	rc->spr.tmp1 = 0;
	rc->spr.j = 0;
	while (rc->spr.j <= rc->sprindex)
	{
		rc->spr.order[rc->spr.j] = rc->spr.j;
		rc->spr.j++;
	}
	rc->spr.j = 0;
}

void	ft_sortsprites(t_rc *rc)
{
	init_sort(rc);
	while (rc->spr.i <= rc->sprindex)
	{
		rc->spr.j = rc->spr.i;
		while (rc->spr.j <= rc->sprindex)
		{
			if (rc->spr.spriteDistance[rc->spr.i]
				< rc->spr.spriteDistance[rc->spr.j])
			{
				rc->spr.tmp = rc->spr.spriteDistance[rc->spr.i];
				rc->spr.spriteDistance[rc->spr.i]
					= rc->spr.spriteDistance[rc->spr.j];
				rc->spr.spriteDistance[rc->spr.j] = rc->spr.tmp;
				rc->spr.tmp1 = rc->spr.order[rc->spr.i];
				rc->spr.order[rc->spr.i] = rc->spr.order[rc->spr.j];
				rc->spr.order[rc->spr.j] = rc->spr.tmp1;
			}
			rc->spr.j++;
		}
		rc->spr.i++;
	}
	rc->spr.i = 0;
}
