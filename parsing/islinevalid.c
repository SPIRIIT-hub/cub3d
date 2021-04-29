/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   islinevalid.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmoulin <bmoulin@42lyon.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/18 11:21:06 by efarin            #+#    #+#             */
/*   Updated: 2021/04/21 14:45:04 by bmoulin          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/cub3d.h"

int	whatstheid(char *line, t_struct *mstruct)
{
	int		i;
	int		j;
	int		result;
	char	*str;

	i = 0;
	j = 0;
	result = -1;
	while (line[i] && line[i] == ' ')
		i++;
	str = ft_substr(line, i, 2);
	if (!(str))
		return (-1);
	while (result != 0 && j <= 7)
	{
		result = ft_strcmp(str, mstruct->args[j]);
		if (result != 0)
			j++;
	}
	wrfree(str);
	if (result != 0)
		return (-1);
	return (j);
}

int	firstpartmap_orther(char *line, t_struct *mstruct, int y)
{
	if (y == 3 && mstruct->pathtoWE == NULL)
	{
		mstruct->pathtoWE = checktheid(line, 'W', 'E');
		return (1);
	}
	if (y == 4 && mstruct->pathtoEA == NULL)
	{
		mstruct->pathtoEA = checktheid(line, 'E', 'A');
		return (1);
	}
	if (y == 5 && mstruct->pathtoS == NULL)
	{
		mstruct->pathtoS = checktheid(line, 'S', ' ');
		return (1);
	}
	return (-1);
}

int	firstpartmap(char *line, t_struct *mstruct, int y)
{
	if (y == 0 && mstruct->Rx == 0 && mstruct->Ry == 0)
		checkelemR(line, mstruct);
	if (y == 0 && mstruct->Rx > 0 && mstruct->Ry > 0)
		return (1);
	if (y == 1 && mstruct->pathtoNO == NULL)
	{
		mstruct->pathtoNO = checktheid(line, 'N', 'O');
		return (1);
	}
	if (y == 2 && mstruct->pathtoSO == NULL)
	{
		mstruct->pathtoSO = checktheid(line, 'S', 'O');
		return (1);
	}
	return (firstpartmap_orther(line, mstruct, y));
}

int	secondpartmap(char *line, t_struct *mstruct, int y)
{
	if (y == 6 && (mstruct->F_B == -1 && mstruct->F_R == -1
			&& mstruct->F_G == -1))
		checkelemF(line, mstruct);
	if (y == 6 && (mstruct->F_R >= 0 && mstruct->F_R <= 255)
		&& (mstruct->F_G >= 0 && mstruct->F_G <= 255)
		&& (mstruct->F_B >= 0 && mstruct->F_B <= 255))
		return (1);
	if (y == 7 && (mstruct->C_B == -1 && mstruct->C_R == -1
			&& mstruct->C_G == -1))
		checkelemC(line, mstruct);
	if (y == 7 && (mstruct->C_R >= 0 && mstruct->C_R <= 255)
		&& (mstruct->C_G >= 0 && mstruct->C_G <= 255)
		&& (mstruct->C_B >= 0 && mstruct->C_B <= 255))
		return (1);
	return (-1);
}

int	shouldiskip(char *line, t_struct *mstruct)
{
	static int	x = 0;
	int			y;

	if (ft_strlen(line) > 0)
		x++;
	if (x <= 8 && ft_strlen(line) == 0)
		return (1);
	if (x > 8 && ft_strlen(line) == 0)
		return (-1);
	if (ft_strlen(line) > 0 && x <= 8)
	{
		y = whatstheid(line, mstruct);
		if (y == -1)
			return (-1);
		if (y >= 0 && y <= 5)
			return (firstpartmap(line, mstruct, y));
		if (y == 6 || y == 7)
			return (secondpartmap(line, mstruct, y));
	}
	else
		return (0);
	return (1);
}
