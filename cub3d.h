/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmoulin <bmoulin@42lyon.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/11 15:39:48 by bmoulin           #+#    #+#             */
/*   Updated: 2021/02/12 08:25:50 by bmoulin          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

#include <mlx.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define KEY_D 2
#define KEY_S 1 
#define KEY_A 0
#define KEY_W 13
#define PI 3.14159265359

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

int             close(int keycode, t_vars *vars);
void            my_mlx_pixel_put(t_vars *data, int x, int y, int color);
int             loop_hook(t_vars *vars);
void			playerposition(t_vars *vars);
int             key_hook(int keycode, t_vars *vars);
void			putsquareWall(t_vars *vars, int x, int y);
void			putsquareVoid(t_vars *vars, int x, int y);
void			putWallInImage(t_vars *vars);
void			ft_putbackground(t_vars *vars);
void			drawline(int x0, int y0, int x1, int y1, t_vars *vars);

#endif