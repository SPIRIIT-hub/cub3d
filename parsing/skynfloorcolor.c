#include "../headers/cub3d.h"
#include "../headers/get_next_line.h"

void	sky_color(char **elem, t_struct *mstruct)
{
	int	i;

	i = 0;
	if (elem != NULL)
	{
		while (elem[i] != 0)
			i++;
		if (i == 3)
		{
			mstruct->C_R = ft_atoi(elem[0]);
			mstruct->C_G = ft_atoi(elem[1]);
			mstruct->C_B = ft_atoi(elem[2]);
		}
		ft_free(elem, i);
	}
}

void	floor_color(char **elem, t_struct *mstruct)
{
	int	i;

	i = 0;
	if (elem != NULL)
	{
		while (elem[i] != 0)
			i++;
		if (i == 3)
		{
			mstruct->F_R = ft_atoi(elem[0]);
			mstruct->F_G = ft_atoi(elem[1]);
			mstruct->F_B = ft_atoi(elem[2]);
		}
		ft_free(elem, i);
	}
}
