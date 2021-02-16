/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmoulin <bmoulin@42lyon.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/09 11:41:34 by bmoulin           #+#    #+#             */
/*   Updated: 2021/02/16 17:55:12 by bmoulin          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int mapX=8,mapY=8,mapS=64;
double px, py, pdx, pdy, pa;

int		map[64] =
{
	1,1,1,1,1,1,1,1,
	1,0,0,1,0,0,0,1,
	1,0,0,1,0,0,0,1,
	1,0,0,1,1,1,0,1,
	1,0,0,0,0,0,0,1,
	1,0,0,1,1,0,0,1,
	1,0,0,0,0,0,0,1,
	1,1,1,1,1,1,1,1
};

// int		map[64] =
// {
// 	1,1,1,1,1,1,1,1,
// 	1,0,0,0,0,0,0,1,
// 	1,0,0,0,0,0,0,1,
// 	1,0,0,0,0,0,0,1,
// 	1,0,0,0,0,0,0,1,
// 	1,0,0,0,0,0,0,1,
// 	1,0,0,0,0,0,0,1,
// 	1,1,1,1,1,1,1,1,
// };

int             close(int keycode, t_vars *vars)
{
    mlx_destroy_window(vars->mlx, vars->win);
	exit(0);
}

void            my_mlx_pixel_put(t_vars *data, int x, int y, int color)
{
    char    *dst;
    dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
    *(unsigned int*)dst = color;
}

int             loop_hook(t_vars *vars)
{
	mlx_put_image_to_window(vars->mlx, vars->win, vars->img, 0, 0);
	return (0);
}


void drawray(int x0, int y0, int x1, int y1, t_vars *vars)
{
  int dx =  abs (x1 - x0), sx = x0 < x1 ? 1 : -1;
  int dy = -abs (y1 - y0), sy = y0 < y1 ? 1 : -1; 
  int err = dx + dy, e2; /* error value e_xy */
  int	count = 0;
	
	int index;
	index = ft_retindex(x0, y0, mapX);
  while (!map[index]){  /* loop */
    my_mlx_pixel_put(vars, x0, y0, 0xFF0000);
    if (x0 == x1 && y0 == y1) break;
    e2 = 2 * err;
    if (e2 >= dy) { err += dy; x0 += sx; } /* e_xy+e_x > 0 */
    if (e2 <= dx) { err += dx; y0 += sy; } /* e_xy+e_y < 0 */
	index = ft_retindex(x0, y0, mapX);
  }
}

void drawray2(int x0, int y0, int x1, int y1, t_vars *vars)
{
  int dx =  abs (x1 - x0), sx = x0 < x1 ? 1 : -1;
  int dy = -abs (y1 - y0), sy = y0 < y1 ? 1 : -1; 
  int err = dx + dy, e2; /* error value e_xy */
  int	count = 0;
	
	int index;
	index = ft_retindex(px, py, mapX);
  while (!map[index]){  /* loop */
    my_mlx_pixel_put(vars, x0, y0, 0xE800FF);
    if (x0 == x1 && y0 == y1) break;
    e2 = 2 * err;
    if (e2 >= dy) { err += dy; x0 += sx; } /* e_xy+e_x > 0 */
    if (e2 <= dx) { err += dx; y0 += sy; } /* e_xy+e_y < 0 */
	index = ft_retindex(x0, y0, mapX);
  }
}

//drawline(px+2, py+2, px + pdx * 50, py + pdy * 50, vars);

void	drawlinetowall(t_vars *vars) // changer pdx et pdy pour s'arreter a un mur.
{
	int		index;
	int		len_rayon;
	double local_px = px;
	double local_py = py;
	double local_pdx = pdx;
	double local_pdy = pdy;
	double count = 0;

	index = ft_retindex(px, py, mapX);
	while (count <= 0.75)
	{
		drawray(px, py, px + pdx * 50000, py + pdy * 50000, vars);
		pdx = cos(pa + count);
		pdy = sin(pa + count);
		count += 0.01;
	}
	count = 0;
	while (count <= 0.75)
	{
		drawray(px, py, px + pdx * 50000, py + pdy * 50000, vars);
		pdx = cos(pa - count);
		pdy = sin(pa - count);
		count += 0.01;
	}
	pdx = local_pdx;
	pdy = local_pdy;
	// drawray(px, py, px + pdx * 50000, py + pdy * 50000, vars);
	if (pa > PI)
	{
		len_rayon = local_px - px;
	}
	else if (pa < PI)
	{
		len_rayon = (py - local_py);
	}
	else
	{
		if (px > py)
			len_rayon = local_px - px;
		else
			len_rayon = local_py - py;
	}
}

void		playerposition(t_vars *vars)
{
	int		i;
	int		j;

	i = px;
	j = py;
	while (++i <= px + 10)
	{
		while (++j <= py + 10)
			my_mlx_pixel_put(vars, i - 5, j- 5, 0xFFFFF);
		j = py;
	}
	drawlinetowall(vars);
	drawline(px+1, py+1, px + pdx * SIZE, py + pdy * SIZE, vars);
	drawline(px+2, py+1, px + pdx * SIZE, py + pdy * SIZE, vars);
	drawline(px+1, py+2, px + pdx * SIZE, py + pdy * SIZE, vars);
	drawline(px+2, py+2, px + pdx * SIZE, py + pdy * SIZE, vars);
}

int             key_hook(int keycode, t_vars *vars)
{
	if (keycode == 53)	close(keycode, vars);
	if (keycode == KEY_A) { ft_putbackground(vars); pa -= 0.1;if (pa < 0)	pa += 2*PI;pdx = cos(pa); pdy = sin(pa); 		playerposition(vars);}
	if (keycode == KEY_D) {	ft_putbackground(vars); pa += 0.1;if (pa > 2*PI)	pa -= 2*PI;pdx = cos(pa);	pdy = sin(pa);	playerposition(vars);}
	if (keycode == KEY_W) { ft_putbackground(vars); px+=pdx; py += pdy; playerposition(vars);}
	if (keycode == KEY_S) { ft_putbackground(vars); px-=pdx; py -= pdy; playerposition(vars);}
	return (0);
}

void		putsquareWall(t_vars *vars, int x, int y)
{
	int		tmpx;
	int		tmpy;
	x *= 	SIZE;
	y *= 	SIZE;
	tmpx = x;
	tmpy = y;
	while (x++ <= tmpx + SIZE)
	{
		while (y++ <= tmpy + SIZE)
			my_mlx_pixel_put(vars, x, y, 0xFFFFFF);
		y = tmpy;
	}
	y = tmpy;
	x = tmpx;
	while (x++ <= tmpx + SIZE)
		my_mlx_pixel_put(vars, x, y, 0x9F9F9F);
	while (y++ <= tmpy + SIZE)
		my_mlx_pixel_put(vars, tmpx, y, 0x9F9F9F);
}

void		putsquareVoid(t_vars *vars, int x, int y)
{
	int		tmpx;
	int		tmpy;
	x *= 	SIZE;
	y *= 	SIZE;
	tmpx = x;
	tmpy = y;
	while (x++ <= tmpx + SIZE)
	{
		while (y++ <= tmpy + SIZE)
			my_mlx_pixel_put(vars, x, y, 0x00000000);
		y = tmpy;
	}
	y = tmpy;
	x = tmpx;
	while (x++ <= tmpx + SIZE)
		my_mlx_pixel_put(vars, x, y, 0x9F9F9F);
	while (y++ <= tmpy + SIZE)
		my_mlx_pixel_put(vars, tmpx, y, 0x9F9F9F);
}

void		putWallInImage(t_vars *vars)
{
	int x,y,xo,yo;
	int tmpx;
	int tmpy;
	for (y=0;y<mapX;y++)
	{
		for(x=0;x<mapX;x++)
		{
			if(map[y*mapX+x] == 1)
				putsquareWall(vars, x, y);
			else
				putsquareVoid(vars, x, y);
			xo=x*mapS;
			yo=y*mapS;
		}
	}
	y--;
	x--;
	tmpy = y * SIZE;
	tmpx = x * SIZE;
	x = 0;
	while (x++ <= tmpx + SIZE)
		my_mlx_pixel_put(vars, x, tmpy + SIZE + 1, 0x00000);
	y = 0;
	while (y++ <= tmpy + SIZE)
		my_mlx_pixel_put(vars, tmpx + SIZE + 1, y, 0x00000);
}

void		ft_putbackground(t_vars *vars)
{
	int x = -1;
	int y = -1;

	while (++x <= 1024)
	{
		while (++y <= 512)
			my_mlx_pixel_put(vars, x, y, 0x00000000);
		y = -1;
	}
	putWallInImage(vars);
}


// void		init_raycaster(t_vars *vars)
// {
// 	t_vars	  cub;

// 	cub.win = mlx_new_window(vars->mlx, 1024, 512, "RayCaster");
// 	mlx_hook(cub.win, 2, 1L<<0, key_hook, &cub);
// 	mlx_loop_hook(vars->mlx, loop_hook, &cub);
// 	cub.img = mlx_new_image(vars->mlx, 1920, 1080);
// 	cub.addr = mlx_get_data_addr(cub.img, &cub.bits_per_pixel, &cub.line_length,
//                                  &cub.endian);
// 	// mlx_put_image_to_window(vars->mlx, vars.win, vars.img, 0, 0);
// }

int             main(void)
{
    t_vars    vars;

	vars.x = -1;
	vars.y = -1;
    vars.mlx = mlx_init();
    vars.win = mlx_new_window(vars.mlx, MINIMAP_HEIGHT, MINIMAP_WIDTH, "Hello world!");

	vars.x = 1;
	vars.y = 2;
	px = vars.x * SIZE;
	py = vars.y * SIZE;
	pa = 0;
	pdx = cos(pa);
	pdy = sin(pa);

	mlx_hook(vars.win, 2, 1L<<0, key_hook, &vars);
	mlx_loop_hook(vars.mlx, loop_hook, &vars);
	vars.img = mlx_new_image(vars.mlx, 1920, 1080);
    vars.addr = mlx_get_data_addr(vars.img, &vars.bits_per_pixel, &vars.line_length, &vars.endian);
	ft_putbackground(&vars);
	playerposition(&vars);
    mlx_put_image_to_window(vars.mlx, vars.win, vars.img, 0, 0);
	// init_raycaster(&vars);
    mlx_loop(vars.mlx);
}
