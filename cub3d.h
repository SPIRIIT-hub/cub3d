#ifndef CUB3D_H
# define CUB3D_H

# include <mlx.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <math.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>
# include <stdarg.h>
# include <stdio.h>
# include <limits.h>
#include <fcntl.h>
#define KEY_D 2
#define KEY_S 1 
#define KEY_A 0
#define KEY_W 13
#define KEY_LEFT 123
#define KEY_RIGHT 124
#define PI 3.14159265359

typedef struct  	s_vars {
        void    	*mlx;
        void    	*win;
		void    	*img;
		char    	*addr;
		int     	bits_per_pixel;
		int     	line_length;
		int     	endian;
        double      posX;
        double      posY;
        double      dirX;
        double      dirY;
        double      planeX;
        double      rayDirX;
        double      rayDirY;
        double      planeY;
        double      cameraX;
}               	t_vars;

void            my_mlx_pixel_put(t_vars *data, int x, int y, int color);
int             key_hook(int keycode, t_vars *vars);
void	        ft_Raycaster(t_vars *vars);

#endif