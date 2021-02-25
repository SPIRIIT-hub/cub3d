/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structstuff.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efarin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/13 12:24:38 by efarin            #+#    #+#             */
/*   Updated: 2021/02/13 12:24:40 by efarin           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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
	mstruct->pathtoNO = NULL;
	mstruct->pathtoSO = NULL;
	mstruct->pathtoWE = NULL;
	mstruct->pathtoEA = NULL;
	mstruct->pathtoS = NULL;

}
