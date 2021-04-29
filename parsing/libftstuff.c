/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libftstuff.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmoulin <bmoulin@42lyon.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/16 10:56:29 by efarin            #+#    #+#             */
/*   Updated: 2021/04/26 13:55:40 by bmoulin          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/cub3d.h"
#include "../headers/get_next_line.h"

char	*ft_strcpy(char *dst, const char *src, size_t dstsize)
{
	size_t		i;

	i = 0;
	if (!src || !dst)
		return (0);
	if (dstsize == 0)
		return (NULL);
	while (i < dstsize && src[i])
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
	return (dst);
}

int	ft_atoi(const char *nptr)
{
	int			i;
	int			s;
	long long	result;

	i = 0;
	s = 1;
	result = 0;
	while ((nptr[i] >= 8 && nptr[i] <= 13) || nptr[i] == ' ')
		i++;
	if (nptr[i] == '+' || nptr[i] == '-')
		if (nptr[++i] == '-')
			s = s * (-1);
	while (nptr[i] >= '0' && nptr[i] <= '9')
	{
		result = (result * 10) + nptr[i] - '0';
		if (result >= INT_MAX)
			return (INT_MAX);
		i++;
	}
	if (nptr[i] != '\0')
		return (-1);
	result = result * s;
	if (result >= INT_MAX)
		return (INT_MAX);
	return ((int)result);
}

size_t	ft_cmpt(char const *s, char c)
{
	size_t	i;
	size_t	count;

	i = 0;
	count = 0;
	while (s[i])
	{
		if (s[i] == c)
			i++;
		if (s[i] != c && s[i] != '\0')
			count++;
		while (s[i] != c && s[i] != '\0')
			i++;
	}
	return (count);
}

char	*ft_free(char **tab, size_t i)
{
	while (i-- > 0)
		wrfree(tab[i]);
	wrfree(tab);
	return (NULL);
}

char	**ft_mem(char const *s, char c)
{
	char	**tab;
	size_t	k;
	size_t	j;
	size_t	i;

	i = -1;
	k = 0;
	j = 0;
	tab = wrmalloc((ft_cmpt(s, c) + 1) * sizeof(char *));
	if (!(tab))
		return (NULL);
	while (s[k] && ++i != ft_cmpt(s, c))
	{
		j = 0;
		while (s[k] == c)
			k++;
		while (s[k] && s[k] != c && s[k++])
			j++;
		tab[i] = wrmalloc((j + 1) * sizeof(char));
		if (!(tab[i]))
			return ((char **)ft_free(tab, i));
	}
	return (tab);
}
