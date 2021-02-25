/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   islinevalid.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efarin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/18 11:21:06 by efarin            #+#    #+#             */
/*   Updated: 2021/02/18 11:21:09 by efarin           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		shouldiskip(char *line, t_struct *mstruct, int a)
{
	static int	x = 0;

	if (a == 1)
	{
		x = 0;
		return (0);
	}
	if (ft_strlen(line) > 0)
		x++;
	if (x <= 8 && ft_strlen(line) == 0)
		return (1);
	if (x > 8 && ft_strlen(line) == 0)
		return (-1);
	if (ft_strlen(line) > 0 && x <= 8)
	{
		if (x == 1)
			checkelemR(line, mstruct);
		if (mstruct->Rx <= 0 || mstruct->Ry <= 0)
			return (-1);
		if (x == 2 && !(mstruct->pathtoNO = checktheid(line, 'N', 'O')))
			return (-1);
		if (x == 3 && !(mstruct->pathtoSO = checktheid(line, 'S', 'O')))
			return (-1);
		if (x == 4 && !(mstruct->pathtoWE = checktheid(line, 'W', 'E')))
			return (-1);
		if (x == 5 && !(mstruct->pathtoEA = checktheid(line, 'E', 'A')))
			return (-1);
		if (x == 6 && !(mstruct->pathtoS = checktheid(line, 'S', ' ')))
			return (-1);
		if (x == 7)
			checkelemF(line, mstruct);
		if (x == 7 && (mstruct->F_R < 0 || mstruct->F_G < 0 || mstruct->F_B < 0
		|| mstruct->F_R > 255 || mstruct->F_G > 255 || mstruct->F_B > 255))
			return (-1);
		if (x == 8)
			checkelemC(line, mstruct);
		if (x == 8 && (mstruct->C_R < 0 || mstruct->C_G < 0 || mstruct->C_B < 0
		|| mstruct->C_R > 255 || mstruct->C_G > 255 || mstruct->C_B > 255))
			return (-1);
	}
	else
		return (0);
	return (1);
}
