#include "../headers/cub3d.h"
#include "../headers/get_next_line.h"

char	**ft_split(char const *s, char c)
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

	src = (char *)s;
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
	size_t	i;

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
	dup = wrmalloc((ft_strlen(s) * sizeof(char) + 1));
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

int	ft_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (s1[i] != '\0' && s2[i] != '\0')
	{
		if (s1[i] != s2[i])
			return (s1[i] - s2[i]);
		i++;
	}
	return (s1[i] - s2[i]);
}
