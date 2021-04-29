#include "../headers/cub3d.h"

void	init_playerposSN(t_rc *rc)
{
	if (rc->pars->position == 'S')
	{
		rc->dirX = 1;
		rc->dirY = 0;
		rc->planeX = 0;
		rc->planeY = -0.66;
	}
	else if (rc->pars->position == 'N')
	{
		rc->dirX = -1;
		rc->dirY = 0;
		rc->planeX = 0;
		rc->planeY = 0.66;
	}
}

void	init_playerposEW(t_rc *rc)
{
	if (rc->pars->position == 'E')
	{
		rc->dirX = 0;
		rc->dirY = 1;
		rc->planeX = 0.66;
		rc->planeY = 0;
	}
	else if (rc->pars->position == 'W')
	{
		rc->dirX = 0;
		rc->dirY = -1;
		rc->planeX = -0.66;
		rc->planeY = 0;
	}
	rc->posX = rc->pars->yplayer + 0.5;
	rc->posY = rc->pars->xplayer + 0.5;
}

void	verif_size_screen(t_rc *rc)
{
	int	sizex;
	int	sizey;

	mlx_get_screen_size(rc, &sizex, &sizey);
	if (rc->pars->Rx > sizex)
		rc->pars->Rx = sizex;
	if (rc->pars->Ry > sizey)
		rc->pars->Ry = sizey;
}

void	save_n_res(t_rc *rc, int argc, char **argv)
{
	if (argc > 3)
	{
		wrdestroy();
		printf("Error, invalid number of arguments.\n");
		exit(0);
	}
	if (argc == 3)
	{
		if (argv[2][0] == '-'
		&& argv[2][1] == '-' && argv[2][2] == 's'
		&& argv[2][3] == 'a' && argv[2][4] == 'v'
		&& argv[2][5] == 'e' && argv[2][6] == '\0')
			rc->save = 1;
		else
		{
			wrdestroy();
			printf("Error, invalid arguments.\n");
			exit(0);
		}
	}
	else
		rc->save = 0;
	verif_size_screen(rc);
}

int	main(int argc, char **argv)
{
	t_rc	rc;

	rc.txtn = wrmalloc(sizeof(t_img *) * 5);
	if (!rc.txtn)
		return (0);
	rc.pars = ismapvalid(argv);
	if (argc <= 0 || rc.pars == NULL)
	{
		printf("Error, map invalid\n");
		wrfree(rc.txtn);
		return (0);
	}
	init_playerposSN(&rc);
	init_playerposEW(&rc);
	save_n_res(&rc, argc, argv);
	init_mlxntxt(&rc);
	ft_Raycaster(&rc);
	if (rc.save == 1)
		save_bmp("save.bmp", &rc);
	mlx_put_image_to_window(rc.mlx, rc.win, rc.img, 0, 0);
	mlx_loop(rc.mlx);
}
