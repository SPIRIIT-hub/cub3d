/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmoulin <bmoulin@42lyon.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/09 11:41:34 by bmoulin           #+#    #+#             */
/*   Updated: 2021/02/12 09:14:30 by bmoulin          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int mapX=8,mapY=8,mapS=64;
double px, py, pdx, pdy, pa;


int		map[64] =
{
	1,1,1,1,1,1,1,1,
	1,0,0,0,0,0,0,1,
	1,0,0,0,0,0,0,1,
	1,0,0,1,1,1,0,1,
	1,0,0,0,0,0,0,1,
	1,0,0,1,1,0,0,1,
	1,0,0,0,0,0,0,1,
	1,1,1,1,1,1,1,1
};

// int		map[64] =
// {
// 	0,0,0,0,0,0,0,0,
// 	0,0,0,0,0,0,0,0,
// 	0,0,0,0,0,0,0,0,
// 	0,1,1,0,0,0,1,0,
// 	0,0,0,0,0,0,0,0,
// 	0,0,0,0,0,0,0,0,
// 	0,0,0,0,0,0,0,0,
// 	0,0,0,0,0,0,0,0
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
	drawline(px, py, px + pdx * 50, py + pdy * 50, vars);
}

int             key_hook(int keycode, t_vars *vars)
{
	if (keycode == 53)	close(keycode, vars);
	if (keycode == KEY_A) { ft_putbackground(vars); pa -= 0.1;if (pa < 0)	pa += 2*PI;pdx = cos(pa); pdy = sin(pa); 		playerposition(vars);}
	if (keycode == KEY_D) {	ft_putbackground(vars); pa += 0.1;if (pa > 2*PI)	pa -= 2*PI;pdx = cos(pa);	pdy = sin(pa);	playerposition(vars);}
	if (keycode == KEY_W) { ft_putbackground(vars); px+=pdx; py += pdy; playerposition(vars);}
	if (keycode == KEY_S) { ft_putbackground(vars); px-=pdx; py -= pdy; playerposition(vars);}
	
	// if (keycode >= 123 && keycode <= 126)
	// {
	// 	if (keycode == 126) // fleche haut
	// 	{
	// 		px+=pdx;
	// 		py+=pdy;
	// 	}
	// 	if (keycode == 125) // fleche bas
	// 	{
	// 		px-=pdx;
	// 		py-=pdy;
	// 	}
	// 	if (keycode == 124) // fleche droite
	// 	{
	// 		pa += 0.1;
	// 		if (pa > 2*PI)
	// 			pa -= 2*PI;
	// 		pdx = cos(pa)*5;
	// 		pdy = sin(pa)*5;
	// 	}
	// 	if (keycode == 123) // fleche gauche
	// 	{
	// 		pa -= 0.1;
	// 		if (pa < 0)
	// 			pa += 2*PI;
	// 		pdx = cos(pa);
	// 		pdy = sin(pa);
	// 	}
	// }
		printf("pdx:%.2f | px:%.2f | pdy:%.2f | py:%.2f | pa:%.2f\n", pdx, px, pdy, py, pa);
    // printf("keycode : %d\n", keycode);
	return (0);
}

void		putsquareWall(t_vars *vars, int x, int y)
{
	int		size = 50;
	int		tmpx;
	int		tmpy;
	x *= 	size;
	y *= 	size;
	tmpx = x;
	tmpy = y;
	while (x++ <= tmpx + size)
	{
		while (y++ <= tmpy + size)
			my_mlx_pixel_put(vars, x, y, 0xFF0000);
		y = tmpy;
	}
	y = tmpy;
	x = tmpx;
	while (x++ <= tmpx + size)
		my_mlx_pixel_put(vars, x, y, 0x00000);
	while (y++ <= tmpy + size)
		my_mlx_pixel_put(vars, tmpx, y, 0x00000);
}

void		putsquareVoid(t_vars *vars, int x, int y)
{
	int		size = 50;
	int		tmpx;
	int		tmpy;
	x *= 	size;
	y *= 	size;
	tmpx = x;
	tmpy = y;
	while (x++ <= tmpx + size)
	{
		while (y++ <= tmpy + size)
			my_mlx_pixel_put(vars, x, y, 0xFFFFFF);
		y = tmpy;
	}
	y = tmpy;
	x = tmpx;
	while (x++ <= tmpx + size)
		my_mlx_pixel_put(vars, x, y, 0x00000);
	while (y++ <= tmpy + size)
		my_mlx_pixel_put(vars, tmpx, y, 0x00000);
}

void		putWallInImage(t_vars *vars)
{
	int x,y,xo,yo;
	int tmpx;
	int tmpy;
	int		size = 50;
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
	tmpy = y * size;
	tmpx = x * size;
	x = 0;
	while (x++ <= tmpx + size)
		my_mlx_pixel_put(vars, x, tmpy + size + 1, 0x00000);
	y = 0;
	while (y++ <= tmpy + size)
		my_mlx_pixel_put(vars, tmpx + size + 1, y, 0x00000);
}

void		ft_putbackground(t_vars *vars)
{
	int x = -1;
	int y = -1;

	while (++x <= 1024)
	{
		while (++y <= 512)
			my_mlx_pixel_put(vars, x, y, 0xBFC2C4);
		y = -1;
	}
	putWallInImage(vars);
}

int             main(void)
{
    t_vars    vars;

	vars.x = -1;
	vars.y = -1;
    vars.mlx = mlx_init();
    vars.win = mlx_new_window(vars.mlx, 1024, 512, "Hello world!");
	


	vars.x = 2;
	vars.y = 3;
	px = vars.x * 50;
	py = vars.y * 50;
	pa = 0;
	pdx = cos(pa);
	pdy = sin(pa);
	
	mlx_hook(vars.win, 2, 1L<<0, key_hook, &vars);
	mlx_loop_hook(vars.mlx, loop_hook, &vars);
	vars.img = mlx_new_image(vars.mlx, 1920, 1080);
    vars.addr = mlx_get_data_addr(vars.img, &vars.bits_per_pixel, &vars.line_length,
                                 &vars.endian);
	ft_putbackground(&vars);

	playerposition(&vars);
    mlx_put_image_to_window(vars.mlx, vars.win, vars.img, 0, 0);
    mlx_loop(vars.mlx);
}  
