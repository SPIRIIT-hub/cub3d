#include "cub3d.h"

#define mapWidth 24
#define mapHeight 24
#define screenWidth 1024
#define screenHeight 512
#define moveSpeed 1
#define rotSpeed 0.0872665

int worldMap[mapWidth][mapHeight]=
{
  {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,2,2,2,2,2,0,0,0,0,3,0,3,0,3,0,0,0,1},
  {1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,3,0,0,0,3,0,0,0,1},
  {1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,2,2,0,2,2,0,0,0,0,3,0,3,0,3,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,4,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,0,4,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,0,0,0,0,5,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,0,4,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,0,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,4,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
};

void			ft_clear(t_vars *vars)
{
	int x = screenHeight;
	int y = screenWidth;

	while (x--)
	{
		while (y--)
			my_mlx_pixel_put(vars, y, x, 0);
		y = screenWidth;
	}
}

void            my_mlx_pixel_put(t_vars *data, int x, int y, int color)
{
    char    *dst;
    dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	//printf("here . %x\n", *(unsigned int*)dst);
	*(unsigned int*)dst = color;
}

void	ft_verLine(int x, int drawstart, int drawend, int color, t_vars *vars)
{
	while (drawstart < drawend)
	{
		my_mlx_pixel_put(vars, x, drawstart, color);
		drawstart++;
	}
}

int             key_hook(int keycode, t_vars *vars)
{
	if (keycode == KEY_W)
    {
      if(worldMap[(int)(vars->posX + vars->dirX * moveSpeed)][(int)(vars->posY)] == 0) vars->posX += vars->dirX * moveSpeed;
      if(worldMap[(int)(vars->posX)][(int)(vars->posY + vars->dirY * moveSpeed)] == 0) vars->posY += vars->dirY * moveSpeed;
	  ft_clear(vars);
	  ft_Raycaster(vars);
    }
    //move backwards if no wall behind you
    if (keycode == KEY_S)
    {
      if(worldMap[(int)(vars->posX - vars->dirX * moveSpeed)][(int)(vars->posY)] == 0) vars->posX -= vars->dirX * moveSpeed;
      if(worldMap[(int)(vars->posX)][(int)(vars->posY - vars->dirY * moveSpeed)] == 0) vars->posY -= vars->dirY * moveSpeed;
	  ft_clear(vars);
	  ft_Raycaster(vars);
    }
    //rotate to the right
    if (keycode == KEY_D)
    {
      //both camera direction and camera plane must be rotated
      double oldDirX = vars->dirX;
      vars->dirX = vars->dirX * cos(-rotSpeed) - vars->dirY * sin(-rotSpeed);
      vars->dirY = oldDirX * sin(-rotSpeed) + vars->dirY * cos(-rotSpeed);
      double oldPlaneX = vars->planeX;
      vars->planeX = vars->planeX * cos(-rotSpeed) - vars->planeY * sin(-rotSpeed);
      vars->planeY = oldPlaneX * sin(-rotSpeed) + vars->planeY * cos(-rotSpeed);
	  ft_clear(vars);
	  ft_Raycaster(vars);
    }
    //rotate to the left
    if (keycode == KEY_A)
    {
      //both camera direction and camera plane must be rotated
      double oldDirX = vars->dirX;
      vars->dirX = vars->dirX * cos(rotSpeed) - vars->dirY * sin(rotSpeed);
      vars->dirY = oldDirX * sin(rotSpeed) + vars->dirY * cos(rotSpeed);
      double oldPlaneX = vars->planeX;
      vars->planeX = vars->planeX * cos(rotSpeed) - vars->planeY * sin(rotSpeed);
      vars->planeY = oldPlaneX * sin(rotSpeed) + vars->planeY * cos(rotSpeed);
	  ft_clear(vars);
	  ft_Raycaster(vars);
    }
	return (0);
}

void	ft_Raycaster(t_vars *vars)
{
	int x = 0;

	
	for(int x = 0; x < screenWidth; x++)
    {
		//calculate ray position and direction
		double cameraX = 2 * x / (double)(screenWidth) - 1; //x-coordinate in camera space
		double rayDirX = vars->dirX + vars->planeX * cameraX;
		double rayDirY = vars->dirY + vars->planeY * cameraX;
		//which box of the map we're in
		int mapX = (int)(vars->posX);
		int mapY = (int)(vars->posY);

		//length of ray from current position to next x or y-side
		double sideDistX;
		double sideDistY;

		//length of ray from one x or y-side to next x or y-side
		double deltaDistX = fabs(1 / rayDirX);
		double deltaDistY = fabs(1 / rayDirY);
		double perpWallDist;

		//what direction to step in x or y-direction (either +1 or -1)
		int stepX;
		int stepY;

		int hit = 0; //was there a wall hit?
		int side; //was a NS or a EW wall hit?

		// Alternative code for deltaDist in case division through zero is not supported
		deltaDistX = (rayDirY == 0) ? 0 : ((rayDirX == 0) ? 1 : fabs(1 / rayDirX));
		deltaDistY = (rayDirX == 0) ? 0 : ((rayDirY == 0) ? 1 : fabs(1 / rayDirY));

		//calculate step and initial sideDist
		if (rayDirX < 0)
		{
			stepX = -1;
			sideDistX = (vars->posX - mapX) * deltaDistX;
		}
		else
		{
			stepX = 1;
			sideDistX = (mapX + 1.0 - vars->posX) * deltaDistX;
		}
		if (rayDirY < 0)
		{
			stepY = -1;
			sideDistY = (vars->posY - mapY) * deltaDistY;
		}
		else
		{
			stepY = 1;
			sideDistY = (mapY + 1.0 - vars->posY) * deltaDistY;
		}
		while (hit == 0)
		{
			//jump to next map square, OR in x-direction, OR in y-direction
			if (sideDistX < sideDistY)
			{
			sideDistX += deltaDistX;
			mapX += stepX;
			side = 0;
			}
			else
			{
			sideDistY += deltaDistY;
			mapY += stepY;
			side = 1;
			}
			//Check if ray has hit a wall
			if (worldMap[mapX][mapY] > 0) hit = 1;
		}
		if (side == 0) perpWallDist = (mapX - vars->posX + (1 - stepX) / 2) / rayDirX;
     	else           perpWallDist = (mapY - vars->posY + (1 - stepY) / 2) / rayDirY;
		int lineHeight = (int)(screenHeight / perpWallDist);

		//calculate lowest and highest pixel to fill in current stripe
		int drawStart = -lineHeight / 2 + screenHeight / 2;
		if(drawStart < 0)drawStart = 0;
		int drawEnd = lineHeight / 2 + screenHeight / 2;
		if(drawEnd >= screenHeight)drawEnd = screenHeight - 1;

		int color;
		switch(worldMap[mapX][mapY])
		{
			case 1:  color = 0xFF2D00;  break; //red
			case 2:  color = 0x00911F;  break; //green
			case 3:  color = 0x00B9FF;   break; //blue
			case 4:  color = 0xFFFFFF;  break; //white
			default: color = 0xFBFF00; break; //yellow
		}

		//give x and y sides different brightness
		if (side == 1) {color = color / 2;}

		//draw the pixels of the stripe as a vertical line
		ft_verLine(x, drawStart, drawEnd, color, vars);
		}
	mlx_put_image_to_window(vars->mlx, vars->win, vars->img, 0, 0);
}

int		main(void)
{
	t_vars vars;
	vars.posX = 22;
	vars.posY = 12;  //x and y start position
  	vars.dirX = -1;
	vars.dirY = 0; //initial direction vector
  	vars.planeX = 0;
	vars.planeY = 0.66; //the 2d raycaster version of camera plane
	// printf("here\n");
	vars.mlx = mlx_init();
    vars.win = mlx_new_window(vars.mlx, screenWidth, screenHeight, "RayCaster");
	mlx_hook(vars.win, 2, 1L<<0, key_hook, &vars);
	mlx_loop_hook(vars.mlx, key_hook, &vars);
	vars.img = mlx_new_image(vars.mlx, screenWidth, screenHeight);
    vars.addr = mlx_get_data_addr(vars.img, &vars.bits_per_pixel, &vars.line_length, &vars.endian);

	ft_Raycaster(&vars);
	mlx_put_image_to_window(vars.mlx, vars.win, vars.img, 0, 0);
	mlx_loop(vars.mlx);
}