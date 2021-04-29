/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   whatsthemap.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmoulin <bmoulin@42lyon.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/15 14:25:41 by efarin            #+#    #+#             */
/*   Updated: 2021/04/15 15:06:36 by bmoulin          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/cub3d.h"
#include "../headers/get_next_line.h"

int	is_in(char c, char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == c)
			return (1);
		i++;
	}
	return (0);
}

int	checkalltab(char **tab, t_struct *mstruct)
{
	int	i;
	int	j;

	i = 0;
	while (tab[i] != NULL)
	{
		j = 0;
		while (tab[i][j] && (is_in(tab[i][j], " NWSE120")))
		{
			if (is_in(tab[i][j], "NWSE"))
			{
				if (mstruct->position != '0')
					return (0);
				mstruct->position = tab[i][j];
				mstruct->xplayer = j;
				mstruct->yplayer = i;
			}
			j++;
		}
		if (tab[i][j] != '\0')
			return (0);
		i++;
	}
	return (1);
}

int	checkthenorth(char **tab)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while ((tab[i][j] == '1' || tab[i][j] == ' ') && tab[i][j])
		j++;
	if (tab[i][j] == '\0')
		return (1);
	return (0);
}

int	thereiszeroortwo(int i, int j, char **tab, t_struct *mstruct)
{
	if (tab[i][j] == '0')
	{
		if (j == 0 || j == (mstruct->lenmax - 1) || tab[i + 1] == NULL)
			return (0);
		if (checkspaces(tab, i, j) == 0)
			return (0);
	}
	else
	{
		if (j == 0 || j == (mstruct->lenmax - 1) || tab[i + 1] == NULL)
			return (0);
		if (checkspaces(tab, i, j) == 0)
			return (0);
	}
	return (1);
}

int	checkthemap(char **tab, t_struct *mstruct)
{
	int	i;
	int	j;

	i = 0;
	if (checkalltab(tab, mstruct) == 0 || checkthenorth(tab) == 0 \
	|| mstruct->position == '0' || checkplayerposition(tab, mstruct) == 0)
		return (0);
	while (tab[i] != NULL)
	{
		j = 0;
		while (tab[i][j])
		{
			if ((tab[i][j] == '0' || tab[i][j] == '2')
			&& thereiszeroortwo(i, j, tab, mstruct) == 0)
				return (0);
			j++;
		}
		i++;
	}
	return (1);
}
