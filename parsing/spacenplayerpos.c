#include "../headers/cub3d.h"
#include "../headers/get_next_line.h"

int	checkspaces(char **tab, int i, int j)
{
	if (tab[i][j + 1] != ' ' && tab[i - 1][j] != ' ' && tab[i][j - 1] != ' ')
		return (1);
	return (0);
}

int	checkplayerposition(char **tab, t_struct *mstruct)
{
	int	i;
	int	j;
	int	k;

	k = 0;
	while (tab[k])
		k++;
	i = mstruct->yplayer;
	j = mstruct->xplayer;
	if (i == k - 1 || i == 0 || j == 0 || j == mstruct->lenmax - 1)
		return (0);
	return (checkspaces(tab, i, j));
}
