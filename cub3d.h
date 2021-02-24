/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmoulin <bmoulin@42lyon.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/11 15:39:48 by bmoulin           #+#    #+#             */
/*   Updated: 2021/02/24 10:12:59 by bmoulin          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

#include <mlx.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <math.h>
#define KEY_D 2
#define KEY_S 1 
#define KEY_A 0
#define KEY_W 13
#define PI 3.14159265359
#define MINIMAP_HEIGHT (int)512
#define MINIMAP_WIDTH (int)512
#define MAP_HEIGHT (int)512
#define MAP_WIDTH (int)1024
#define FOV 1.0472
#define SIZE (int)(MINIMAP_HEIGHT / 8)

typedef struct		s_list
{
      void			*content;
      struct s_list	*next;
}					t_list;

typedef struct  s_cub {
        void    *mlx;
        void    *win;
		int		x;
		int		y;
		void    *img;
		char    *addr;
		int     bits_per_pixel;
		int     line_length;
		int     endian;
}               t_cub;

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
		t_cub	*cub;
}               t_vars;

int             close_exit(int keycode, t_vars *vars);
void            my_mlx_pixel_put(t_vars *data, int x, int y, int color);
int             loop_hook(t_vars *vars);
void			playerposition(t_vars *vars);
int             key_hook(int keycode, t_vars *vars);
void			putsquareWall(t_vars *vars, int x, int y);
void			putsquareVoid(t_vars *vars, int x, int y);
void			putWallInImage(t_vars *vars);
void			ft_putbackground(t_vars *vars);
void			drawline(int x0, int y0, int x1, int y1, t_vars *vars);
double			drawray(int x0, int y0, int x1, int y1, t_vars *vars);
int				ft_retindex(int px, int py, int mapX);
void			ft_putbackground2(t_vars *vars);
void			*wrmalloc(unsigned long size);
int				wrfree(void *ptr);
void			wrdestroy(void);
void			ft_lstadd_back(t_list **alst, t_list *new);
t_list			*ft_lstlast(t_list *lst);


#endif