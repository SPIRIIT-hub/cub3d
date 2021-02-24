/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmoulin <bmoulin@42lyon.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/12 07:47:34 by bmoulin           #+#    #+#             */
/*   Updated: 2021/02/24 13:32:37 by bmoulin          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

extern int SIZE;

void drawline(int x0, int y0, int x1, int y1, t_vars *vars)
{
  int dx =  abs (x1 - x0), sx = x0 < x1 ? 1 : -1;
  int dy = -abs (y1 - y0), sy = y0 < y1 ? 1 : -1; 
  int err = dx + dy, e2; /* error value e_xy */

  while (1){  /* loop */
    my_mlx_pixel_put(vars, x0, y0, 0x00000000);
    if (x0 == x1 && y0 == y1) break;
    e2 = 2 * err;
    if (e2 >= dy) { err += dy; x0 += sx; } /* e_xy+e_x > 0 */
    if (e2 <= dx) { err += dx; y0 += sy; } /* e_xy+e_y < 0 */
  }
}

int		ft_retindex(int px, int py, int mapX)
{
	int	   tmpx;
	int	   tmpy;
	int	   place;

	tmpx = (px / SIZE);
	tmpy = (py / SIZE);
	tmpy++;
	place = floor((int)((tmpy * mapX + tmpx) - mapX));
	if (place < 0)
		place = floor((int)(tmpy * mapX + tmpx));
	return (place);
}
