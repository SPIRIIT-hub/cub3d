/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmoulin <bmoulin@42lyon.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/09 11:41:34 by bmoulin           #+#    #+#             */
/*   Updated: 2021/02/10 14:07:57 by bmoulin          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <mlx.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct  s_vars {
        void    *mlx;
        void    *win;
		int		x;
		int		y;
		void    *img;
		char    *addr;
		int     bits_per_pixel;
		int     line_length;
		int     endian;
}               t_vars;

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

int             key_hook(int keycode, t_vars *vars)
{
	if (keycode == 53)
		close(keycode, vars);
	vars->x = 0;
	vars->y = 0;
	if (keycode == 12)
	{
		while (++vars->x < 200)
		{
			while (++vars->y < 200)
				my_mlx_pixel_put(vars, vars->x, vars->y, 0x008FFF);
			vars->y = 0;
		}
	}
    printf("keycode : %d\n", keycode);
	return (0);
}

int             loop_hook(t_vars *vars)
{
	mlx_put_image_to_window(vars->mlx, vars->win, vars->img, 0, 0);
	return (0);
}

int             main(void)
{
    t_vars    vars;

	vars.x = 0;
	vars.y = 0;
    vars.mlx = mlx_init();
    vars.win = mlx_new_window(vars.mlx, 540, 540, "Hello world!");
	mlx_key_hook(vars.win, key_hook, &vars);
	mlx_loop_hook(vars.mlx, loop_hook, &vars);
	vars.img = mlx_new_image(vars.mlx, 1920, 1080);
    vars.addr = mlx_get_data_addr(vars.img, &vars.bits_per_pixel, &vars.line_length,
                                 &vars.endian);
	while (++vars.x < 200)
	{
		while (++vars.y < 200)
    		my_mlx_pixel_put(&vars, vars.x, vars.y, 0xFF0000);
		vars.y = 0;
	}
    mlx_put_image_to_window(vars.mlx, vars.win, vars.img, 0, 0);
    mlx_loop(vars.mlx);
}  
