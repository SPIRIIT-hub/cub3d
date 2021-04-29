/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmoulin <bmoulin@42lyon.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/18 11:00:20 by efarin            #+#    #+#             */
/*   Updated: 2021/04/10 19:16:11 by bmoulin          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>

typedef struct s_gnl
{
	int		i;
	int		l;
	int		r;
	char	c;
	char	*tmp;
}	t_gnl;

int	get_next_line(int fd, char **line);

#endif