#include "../headers/cub3d.h"
#include "../headers/get_next_line.h"

void	checkelemR(char *line, t_struct *mstruct)
{
	char	**elem;
	int		i;
	int		j;

	i = 0;
	j = 0;
	elem = ft_split(line, ' ');
	while (elem[i] != 0)
		i++;
	if (i == 3 && ft_strlen(elem[0]) == 1 && elem[0][0] == 'R')
	{
		while (elem[1][j] >= '0' && elem[1][j] <= '9' && elem[1][j])
			j++;
		if (elem[1][j] == '\0' && j > 0)
		{
			mstruct->Rx = ft_atoi(elem[1]);
			j = 0;
			while (elem[2][j] >= '0' && elem[2][j] <= '9')
				j++;
			if (elem[2][j] == '\0' && j > 0)
				mstruct->Ry = ft_atoi(elem[2]);
		}
	}
	ft_free(elem, i);
}

char	*checktheid(char *line, char a, char b)
{
	int	i;
	int	start;

	i = 0;
	while (line[i] && line[i] == ' ')
		i++;
	if (line[i] && line[i] == a && ++i)
	{
		if (line[i] && line[i] == b && ++i)
		{
			if (line[i] && !(line[i] != ' ' && b != ' '))
			{
				start = i;
				while (line[i])
					i++;
				if (i > start)
					return (ft_strtrim(ft_substr(line, start, i), " "));
			}
		}
	}
	return (NULL);
}

void	checkelemF(char *line, t_struct *mstruct)
{
	int		i;
	char	**elem;
	int		start;

	i = 0;
	elem = NULL;
	if (line[ft_strlen(line) - 1] == ',')
		return ;
	while (line[i] && line[i] == ' ')
		i++;
	if (line[i] == 'F' && ++i)
	{
		start = i;
		if (line[i] == ' ')
			while (line[i])
				i++;
		if (i > start)
			elem = ft_split(ft_strtrim(ft_substr(line, start, i), " "), ',');
		i = 0;
		floor_color(elem, mstruct);
	}
}

void	checkelemC(char *line, t_struct *mstruct)
{
	int		i;
	char	**elem;
	int		start;

	i = 0;
	elem = NULL;
	if (line[ft_strlen(line) - 1] == ',')
		return ;
	while (line[i] && line[i] == ' ')
		i++;
	if (line[i] == 'C' && ++i)
	{
		start = i;
		if (line[i] == ' ')
			while (line[i])
				i++;
		if (i > start)
			elem = ft_split(ft_strtrim(ft_substr(line, start, i), " "), ',');
		i = 0;
		sky_color(elem, mstruct);
	}
}
