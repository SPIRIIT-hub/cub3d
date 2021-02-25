/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efarin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/25 17:01:11 by efarin            #+#    #+#             */
/*   Updated: 2020/12/07 17:57:29 by efarin           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static size_t	ft_check(char c, char const *set)
{
	size_t i;

	i = 0;
	while (set[i])
	{
		if (set[i] == c)
			return (1);
		i++;
	}
	return (0);
}

static char		*ft_putzero(char *str, size_t i)
{
	str = malloc(1 * sizeof(char));
	str[i] = '\0';
	return (str);
}

char			*ft_strtrim(char const *s1, char const *set)
{
	size_t	i;
	size_t	l;
	size_t	j;
	char	*str;

	if (s1 == 0)
		return (NULL);
	if (set == 0)
		return (ft_strdup(s1));
	i = 0;
	j = 0;
	l = ft_strlen(s1) - 1;
	str = NULL;
	while (ft_check(s1[j], set) == 1 && s1[j])
		j++;
	while (ft_check(s1[l], set) == 1 && l > 0)
		l--;
	if (j == ft_strlen(s1))
		return (ft_putzero(str, i));
	if ((str = malloc((l - j + 2) * sizeof(char))) == NULL)
		return (NULL);
	while (j != (l + 1))
		str[i++] = s1[j++];
	str[i] = '\0';
	return (str);
}
