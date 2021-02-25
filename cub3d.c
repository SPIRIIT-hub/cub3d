/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmoulin <bmoulin@42lyon.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/09 11:41:34 by bmoulin           #+#    #+#             */
/*   Updated: 2021/02/25 14:29:02 by bmoulin          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// int mapX=15,mapY=8,mapS=120;
// int	cx = 0, cy = MAP_WIDTH;
// double px, py, pdx, pdy, rdx, rdy, pa;
int SIZE = 16;
// int MINIMAP_HEIGHT = 0;
// int MINIMAP_WIDTH = 0;

// int		map[88] =
// {
// 	1,1,1,1,1,1,1,1,32,32,32,
// 	1,0,0,1,0,0,0,1,32,32,32,
// 	1,0,0,1,0,0,0,1,32,32,32,
// 	1,0,0,1,1,1,0,1,32,32,32,
// 	1,0,0,0,0,0,0,1,1,1,1,
// 	1,0,0,1,1,0,0,0,0,0,1,
// 	1,0,0,0,0,0,0,0,0,0,1,
// 	1,1,1,1,1,1,1,1,1,1,1
// };

// int		map[144] =
// {
// 	1,1,1,1,1,1,1,1,32,32,32,32,
// 	1,0,0,0,0,0,0,0,1,32,32,32,
// 	1,0,0,0,0,1,0,0,1,32,32,32,
// 	1,0,0,0,0,0,0,0,1,32,32,32,
// 	1,0,0,1,1,1,1,0,1,1,1,1,
// 	1,0,0,0,0,0,0,0,0,0,0,1,
// 	1,0,0,0,1,0,0,0,0,0,0,1,
// 	1,0,0,0,0,0,0,0,1,1,1,1,
// 	1,1,1,1,1,1,1,1,32,32,32,32,
// 	0,0,0,0,0,0,0,0,0,0,0,0
// };

// char		map[120] =
// {
// 	6,6,6,6,1,1,1,1,1,1,1,1,1,1,1,
// 	6,6,6,6,1,0,0,1,0,0,0,0,0,0,1,
// 	6,6,6,6,1,0,0,1,0,0,0,0,0,0,1,
// 	6,6,6,6,1,0,0,1,1,1,0,0,0,0,1,
// 	6,6,6,6,1,0,0,0,0,0,0,0,0,0,1,
// 	6,6,6,6,1,0,0,1,1,0,0,0,0,0,1,
// 	6,6,6,6,1,0,0,0,0,0,0,0,0,0,1,
// 	6,6,6,6,1,1,1,1,1,1,1,1,1,1,1
// };

int             close_exit(int keycode, t_vars *vars)
{
	// mlx_destroy_window(vars->mlx, vars->cub->win);
    // mlx_destroy_window(vars->mlx, vars->win);
	wrdestroy();
	exit(0);
}

void            my_mlx_pixel_put(t_vars *data, int x, int y, int color)
{
    char    *dst;
    dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
    *(unsigned int*)dst = color;
}

void            my_mlx_pixel_put2(t_vars *data, int x, int y, int color)
{
    char    *dst;
    dst = data->cub->addr + (y * data->cub->line_length + x * (data->cub->bits_per_pixel / 8));
    *(unsigned int*)dst = color;
}

int             loop_hook(t_vars *vars)
{
	// mlx_put_image_to_window(vars->mlx, vars->win, vars->img, 0, 0);
	// mlx_put_image_to_window(vars->mlx, vars->cub->win, vars->cub->img, 0, 0);
	return (0);
}

double drawray(int x0, int y0, int x1, int y1, t_vars *vars)
{
  int dx =  abs (x1 - x0), sx = x0 < x1 ? 1 : -1;
  int dy = -abs (y1 - y0), sy = y0 < y1 ? 1 : -1; 
  int err = dx + dy, e2; /* error value e_xy */
  int	count = 0;
  double distance;

	int index;
	index = ft_retindex(x0, y0, vars->data->mapX);
  while (vars->pars->map[index] != '1'){  /* loop */
    my_mlx_pixel_put(vars, x0, y0, 0xFF0000);
    if (x0 == x1 && y0 == y1) break;
    e2 = 2 * err;
    if (e2 >= dy) { err += dy; x0 += sx; } /* e_xy+e_x > 0 */
    if (e2 <= dx) { err += dx; y0 += sy; } /* e_xy+e_y < 0 */
	index = ft_retindex(x0, y0, vars->data->mapX);
  }
	distance = sqrt((vars->data->px-x0)*(vars->data->px-x0) + (vars->data->py-y0)*(vars->data->py-y0));
	return (distance);
}

void drawray2(int x0, int y0, int x1, int y1, t_vars *vars)
{
  int dx =  abs (x1 - x0), sx = x0 < x1 ? 1 : -1;
  int dy = -abs (y1 - y0), sy = y0 < y1 ? 1 : -1; 
  int err = dx + dy, e2; /* error value e_xy */
  int	count = 0;
	
	int index;
	index = ft_retindex(vars->data->px, vars->data->py, vars->data->mapX);
  while (!vars->pars->map[index]){  /* loop */
    my_mlx_pixel_put(vars, x0, y0, 0xE800FF);
    if (x0 == x1 && y0 == y1) break;
    e2 = 2 * err;
    if (e2 >= dy) { err += dy; x0 += sx; } /* e_xy+e_x > 0 */
    if (e2 <= dx) { err += dx; y0 += sy; } /* e_xy+e_y < 0 */
	index = ft_retindex(x0, y0, vars->data->mapX);
  }
}

void	RayCaster(double distance, t_vars *vars)
{
	int loop_pixel = vars->data->map_width;
	int pixel_len = ceil(((vars->data->map_height/2)/distance) * SIZE);
	int mid_pix_len = pixel_len / 2;
	int i = 0;
	int sky = ((vars->data->map_height - pixel_len) / 2) + 1;
	int floor = sky;
	// if (colortab >= 4)
	// 	colortab = 0;
	// ft_putbackground2(&vars->cub, color[0]);
	// printf("pixel_len : %d\n", pixel_len);
	vars->data->cx = vars->data->map_height/2;
	while (mid_pix_len-- && vars->data->cx >= 0)
	{
		my_mlx_pixel_put2(vars, vars->data->cy, vars->data->cx--, 0xFF0000);
	}
	while (sky-- && vars->data->cx >= 0)
		my_mlx_pixel_put2(vars, vars->data->cy, vars->data->cx--, 0x0097FF); // sky
	my_mlx_pixel_put2(vars, vars->data->cy, 0, 0x0097FF);
	mid_pix_len = pixel_len / 2;
	vars->data->cx = vars->data->map_height/2;
	while (mid_pix_len-- && vars->data->cx <= vars->data->map_height)
	{
		my_mlx_pixel_put2(vars, vars->data->cy, vars->data->cx++, 0xFF0000);
	}
	while (floor-- && vars->data->cx <= vars->data->map_height)
		my_mlx_pixel_put2(vars, vars->data->cy, vars->data->cx++, 0xFFFFF); // floor
	vars->data->cy--;
	if (vars->data->cy <= 0)
		vars->data->cy = vars->data->map_width;
	// if (cy >= MAP_WIDTH)
	// 	cy = 0;

	// mlx_put_image_to_window(vars->mlx, vars->cub.win, vars->cub.img, 0, 0);
}

void	drawlinetowall(t_vars *vars) // changer pdx et pdy pour s'arreter a un mur.
{
	int		index;
	int		len_rayon;
	double local_px = vars->data->px;
	double local_py = vars->data->py;
	double local_pdx = vars->data->pdx;
	double local_pdy = vars->data->pdy;
	double angle_min = vars->data->pa + FOV/2;
	double inc = FOV/vars->data->map_width;
	vars->data->rdx = cos(angle_min);
	vars->data->rdy = sin(angle_min);

	index = ft_retindex(vars->data->px, vars->data->py, vars->data->mapX);
	int i = 0;
	while (i < vars->data->map_width)
	{
		RayCaster(drawray(vars->data->px, vars->data->py, vars->data->px + vars->data->rdx * 50000, vars->data->py + vars->data->rdy * 50000, vars), vars);
		angle_min -= inc;
		if (angle_min < 0)
			angle_min = 2*PI + angle_min;
		vars->data->rdx = cos(angle_min);
		vars->data->rdy = sin(angle_min);
		i++;
	}
	mlx_put_image_to_window(vars->mlx, vars->cub->win, vars->cub->img, 0, 0);
	mlx_put_image_to_window(vars->mlx, vars->win, vars->img, 0, 0);
}

void		playerposition(t_vars *vars)
{
	int		i;
	int		j;

	i = vars->data->px;
	j = vars->data->py;
	while (++i <= vars->data->px + 10)
	{
		while (++j <= vars->data->py + 10)
			my_mlx_pixel_put(vars, i - 5, j- 5, 0xFFFFF);
		j = vars->data->py;
	}
	drawlinetowall(vars);
}

int             key_hook(int keycode, t_vars *vars)
{
	if (keycode == 53)	close_exit(keycode, vars);
	if (keycode == KEY_A) { ft_putbackground(vars); vars->data->pa -= 0.1;if (vars->data->pa < 0)	vars->data->pa += 2*PI;vars->data->pdx = cos(vars->data->pa); vars->data->pdy = sin(vars->data->pa); 		playerposition(vars);}
	if (keycode == KEY_D) {	ft_putbackground(vars); vars->data->pa += 0.1;if (vars->data->pa > 2*PI)	vars->data->pa -= 2*PI;vars->data->pdx = cos(vars->data->pa);	vars->data->pdy = sin(vars->data->pa);	playerposition(vars);}
	if (keycode == KEY_W) {
		if (vars->pars->map[ft_retindex(vars->data->px + (vars->data->pdx * 2), vars->data->py + (vars->data->pdy * 2), vars->data->mapX)] != '1')
		{
			ft_putbackground(vars); vars->data->px+=(vars->data->pdx) * 2; vars->data->py += (vars->data->pdy) * 2;
			playerposition(vars);
		}
	}
	if (keycode == KEY_S) {
		if (vars->pars->map[ft_retindex(vars->data->px - (vars->data->pdx * 2), vars->data->py - (vars->data->pdy * 2), vars->data->mapX)] != '1')
		{
			ft_putbackground(vars); vars->data->px-=(vars->data->pdx) * 2; vars->data->py -= (vars->data->pdy) * 2;
			playerposition(vars);
		}
	}
	return (0);
}

int             minimap_key_hook(int keycode, t_vars *vars)
{
	if (keycode == 53)	close_exit(keycode, vars);
	// if (keycode == KEY_A) { ft_putbackground(vars); pa -= 0.1;if (pa < 0)	pa += 2*PI;pdx = cos(pa); pdy = sin(pa); 		playerposition(vars);}
	// if (keycode == KEY_D) {	ft_putbackground(vars); pa += 0.1;if (pa > 2*PI)	pa -= 2*PI;pdx = cos(pa);	pdy = sin(pa);	playerposition(vars);}
	// if (keycode == KEY_W) {
	// 	if (!map[ft_retindex(px + (pdx * 2), py + (pdy * 2), mapX)])
	// 		playerposition(vars->cub);
	// }
	// if (keycode == KEY_S) {
	// 	if (!map[ft_retindex(px - (pdx * 2), py - (pdy * 2), mapX)])
	// 		playerposition(vars->cub);
	// }
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
	for (y=0;y<vars->data->mapY;y++)
	{
		for(x=0;x<vars->data->mapX;x++)
		{
			if(vars->pars->map[y*vars->data->mapX+x] == '1')
				putsquareWall(vars, x, y);
			else if (vars->pars->map[y*vars->data->mapX+x] != '1')
				putsquareVoid(vars, x, y);
			xo=x*vars->data->mapS;
			yo=y*vars->data->mapS;
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

	while (++x <= vars->data->minimap_height)
	{
		while (++y <= vars->data->minimap_width)
			my_mlx_pixel_put(vars, x, y, 0x00000000);
		y = -1;
	}
	putWallInImage(vars);
}

void		ft_putbackground2(t_vars *vars)
{
	int x = -1;
	int y = -1;

	while (++x <= vars->data->minimap_width)
	{
		while (++y <= vars->data->minimap_height)
			my_mlx_pixel_put(vars, x, y, 0x00000000);
		y = -1;
	}
}

void		init_raycaster(t_vars *vars)
{
	vars->cub->win = mlx_new_window(vars->mlx, vars->data->map_width, vars->data->map_height, "RayCaster");
	mlx_hook(vars->cub->win, 2, 1L<<0, key_hook, vars);
	mlx_loop_hook(vars->mlx, key_hook, vars);
	vars->cub->img = mlx_new_image(vars->mlx, vars->data->map_width, vars->data->map_height + 2);
	vars->cub->addr = mlx_get_data_addr(vars->cub->img, &vars->cub->bits_per_pixel, &vars->cub->line_length,
                                 &vars->cub->endian);
}

int             main(int arc, char **arv)
{
    t_vars    *vars;

	vars = wrmalloc(sizeof(t_vars));
	vars->cub = wrmalloc(sizeof(t_cub));
	vars->data = wrmalloc(sizeof(t_data));
	vars->pars = wrmalloc(sizeof(t_struct));

	// if (mapX >= mapY)
	// 	SIZE = MINIMAP_HEIGHT / mapX;
	// else
	// 	SIZE = MINIMAP_HEIGHT / mapY;
	if (arc <= 0 || (vars->pars = ismapvalid(arv)) == NULL)
	{
		printf("Error, map invalid\n");
		return (0);
	}
	// printf("vars->pars->map : |%s|\n", vars->pars->map);
	// return (0);
	vars->data->mapS = ft_strlen(vars->pars->map);
	vars->data->mapX = vars->pars->lenmax;
	vars->data->mapY = vars->data->mapS / vars->data->mapX;
	vars->data->minimap_height = vars->data->mapX * SIZE;
	vars->data->minimap_width = vars->data->mapY * SIZE;
	vars->data->map_height = vars->pars->Ry;
	vars->data->map_width = vars->pars->Rx;
	vars->data->x = vars->pars->xplayer;
	vars->data->y = vars->pars->yplayer;
	vars->data->cx = 0;
	vars->data->cy = vars->data->map_width;
	printf("MapX : %d\n", vars->data->mapX);
	printf("MapY : %d\n", vars->data->mapY);
	// printf("vars->data->map_height : %d\n", vars->data->map_height);
	// printf("vars->data->map_width : %d\n", vars->data->map_width);


	// MINIMAP_HEIGHT = mapX * SIZE;
	// MINIMAP_WIDTH = mapY * SIZE;

	// vars->x = -1;
	// vars->y = -1;
    vars->mlx = mlx_init();
    vars->win = mlx_new_window(vars->mlx, vars->data->minimap_height, vars->data->minimap_width, "MiniMap");

	// vars->x = 6;
	// vars->y = 1;
	// px = (vars->x * SIZE) + SIZE / 2;
	// py = (vars->y * SIZE) + SIZE / 2;
	// pa = 0;
	// pdx = cos(pa);
	// pdy = sin(pa);

	vars->data->px = (vars->data->x * SIZE) + SIZE / 2;
	vars->data->py = (vars->data->y * SIZE) + SIZE / 2;
	vars->data->pa = 0;
	vars->data->pdx = cos(vars->data->pa);
	vars->data->pdy = sin(vars->data->pa);

	mlx_hook(vars->win, 2, 1L<<0, minimap_key_hook, &vars);
	mlx_loop_hook(vars->mlx, loop_hook, &vars);
	vars->img = mlx_new_image(vars->mlx, vars->data->minimap_height, vars->data->minimap_width);
    vars->addr = mlx_get_data_addr(vars->img, &vars->bits_per_pixel, &vars->line_length, &vars->endian);
	init_raycaster(vars);
	ft_putbackground(vars);
	// printf("vars->addr : %lld\n", vars->addr[0]);
	playerposition(vars);
    mlx_put_image_to_window(vars->mlx, vars->win, vars->img, 0, 0);
	mlx_put_image_to_window(vars->mlx, vars->cub->win, vars->cub->img, 0, 0);
    mlx_loop(vars->mlx);
}
