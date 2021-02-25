/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libftstuff.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efarin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/16 10:56:29 by efarin            #+#    #+#             */
/*   Updated: 2021/02/16 10:56:30 by efarin           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "get_next_line.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t		i;
	size_t		j;
	char		*str;

	i = 0;
	j = 0;
	if (!s)
		return (NULL);
	if (start >= ft_strlen(s))
		str = malloc(sizeof(char));
	else if (len > (ft_strlen(s) - start))
		str = malloc((ft_strlen(s) - start + 1) * sizeof(char));
	else
		str = malloc((len + 1) * sizeof(char));
	if (str == NULL)
		return (NULL);
	while (i != start && s[i])
		i++;
	while (s[i] && j < len)
		str[j++] = s[i++];
	str[j] = '\0';
	return (str);
}

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
	long int	result;

	i = 0;
	s = 1;
	result = 0;
	while ((nptr[i] >= 8 && nptr[i] <= 13) || nptr[i] == ' ')
		i++;
	if (nptr[i] == '+' || nptr[i] == '-')
	{
		if (nptr[i] == '-')
			s = s * (-1);
		i++;
	}
	while (nptr[i] >= '0' && nptr[i] <= '9')
	{
		result = (result * 10) + nptr[i] - '0';
		i++;
	}
	if (nptr[i] != '\0')
		return (-1);
	result = result * s;
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

char		*ft_free(char **tab, size_t i)
{
	while (i-- > 0)
		free(tab[i]);
	free(tab);
	return (NULL);
}

char		**ft_mem(char const *s, char c)
{
	char	**tab;
	size_t	k;
	size_t	j;
	size_t	i;

	i = 0;
	k = 0;
	j = 0;
	if (!(tab = malloc((ft_cmpt(s, c) + 1) * sizeof(char *))))
		return (NULL);
	while (s[k] && i != ft_cmpt(s, c))
	{
		j = 0;
		while (s[k] == c)
			k++;
		while (s[k] != c && s[k])
		{
			k++;
			j++;
		}
		if (!(tab[i] = malloc((j + 1) * sizeof(char))))
			return ((char **)ft_free(tab, i));
		i++;
	}
	return (tab);
}

char			**ft_split(char const *s, char c)
{
	char	**tab;
	size_t	i;
	size_t	j;
	size_t	k;

	i = 0;
	k = 0;
	if (s == 0)
		return (NULL);
	tab = ft_mem(s, c);
	if (tab == NULL)
		return (NULL);
	while (s[k] && i != ft_cmpt(s, c))
	{
		j = 0;
		while (s[k] == c)
			k++;
		while (s[k] != c && s[k])
			tab[i][j++] = s[k++];
		tab[i][j] = '\0';
		i++;
	}
	tab[i] = 0;
	return (tab);
}

void	ft_bzero(void *s, size_t n)
{
	size_t	i;
	int		j;
	char	*src;

	src = (char*)s;
	i = 0;
	j = 0;
	if (n == 0)
		return ;
	while (i < n)
	{
		src[j] = '\0';
		j++;
		i++;
	}
}

size_t	ft_strlen(const char *s)
{
	size_t i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

char	*ft_strdup(const char *s)
{
	char	*dup;
	int		i;

	i = 0;
	dup = NULL;
	dup = malloc((ft_strlen(s) * sizeof(char) + 1));
	if (dup == NULL)
		return (0);
	while (s[i])
	{
		dup[i] = s[i];
		i++;
	}
	dup[i] = '\0';
	return (dup);
}