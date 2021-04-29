/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structstuff.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmoulin <bmoulin@42lyon.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/13 12:24:38 by efarin            #+#    #+#             */
/*   Updated: 2021/04/10 17:52:06 by bmoulin          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/cub3d.h"

void	split_structinit(t_struct *mstruct)
{
	mstruct->pathtoNO = NULL;
	mstruct->pathtoSO = NULL;
	mstruct->pathtoWE = NULL;
	mstruct->pathtoEA = NULL;
	mstruct->pathtoS = NULL;
	mstruct->args[0] = "R ";
	mstruct->args[1] = "NO";
	mstruct->args[2] = "SO";
	mstruct->args[3] = "WE";
	mstruct->args[4] = "EA";
	mstruct->args[5] = "S ";
	mstruct->args[6] = "F ";
	mstruct->args[7] = "C ";
}

void	structinit(t_struct *mstruct)
{
	mstruct->lenmax = 0;
	mstruct->Rx = 0;
	mstruct->Ry = 0;
	mstruct->i = 0;
	mstruct->northside = 0;
	mstruct->position = '0';
	mstruct->xplayer = 0;
	mstruct->yplayer = 0;
	mstruct->F_B = -1;
	mstruct->F_G = -1;
	mstruct->F_R = -1;
	mstruct->C_B = -1;
	mstruct->C_R = -1;
	mstruct->C_G = -1;
	split_structinit(mstruct);
}
