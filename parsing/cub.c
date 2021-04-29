/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmoulin <bmoulin@42lyon.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/10 10:33:03 by efarin            #+#    #+#             */
/*   Updated: 2021/04/21 15:01:34 by bmoulin          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/get_next_line.h"
#include "../headers/cub3d.h"

char	**fromlsttotab(t_list **alst, t_struct *mstruct)
{
	char			**tab;
	int				i;
	t_list			*lst;

	i = 0;
	lst = *alst;
	mstruct->lenmax = getlenmax(&lst);
	tab = wrmalloc((ft_lstsize(lst) + 1) * sizeof(char *));
	if (!(tab))
		return (NULL);
	while (lst != NULL)
	{
		tab[i] = wrmalloc((mstruct->lenmax + 1) * sizeof(char));
		if (!(tab[i]))
			return (NULL);
		ft_bzero(tab[i], mstruct->lenmax + 1);
		tab[i] = ft_strcpy(tab[i], lst->content, ft_strlen(lst->content));
		free(lst->content);
		lst = lst->next;
		i++;
	}
	tab[i] = NULL;
	return (tab);
}

char	**fillthetabwithspaces(char **tab, t_struct *mstruct)
{
	int	i;
	int	j;

	i = 0;
	while (tab[i] != NULL)
	{
		j = 0;
		while (tab[i][j])
			j++;
		while (j < mstruct->lenmax)
		{
			tab[i][j] = ' ';
			j++;
			if (j == mstruct->lenmax)
				tab[i][j] = '\0';
		}
		i++;
	}
	return (tab);
}

int	checkthefilename(char **arv)
{
	int	len;
	int	i;

	i = 0;
	len = ft_strlen(arv[1]);
	if (len > 1)
		i = len - 1;
	else
		return (-1);
	if (arv[1][i] == 'b')
		if (arv[1][i - 1] == 'u')
			if (arv[1][i - 2] == 'c')
				if (arv[1][i - 3] == '.')
					return (1);
	return (-1);
}

t_struct	*ismapvalid(char **arv)
{
	int				fd;
	t_list			*lst;
	char			**tab;
	t_struct		*mstruct;

	mstruct = wrmalloc(sizeof(t_struct));
	if (!(mstruct))
		return (NULL);
	structinit(mstruct);
	fd = open(arv[1], O_RDONLY);
	if (fd == -1)
		return (NULL);
	if (checkthefilename(arv) == -1)
		return (NULL);
	lst = makelst(fd, mstruct);
	if (lst == NULL)
		return (NULL);
	tab = fromlsttotab(&lst, mstruct);
	if (tab != NULL)
		tab = fillthetabwithspaces(tab, mstruct);
	if (checkthemap(tab, mstruct) != 1)
		return (NULL);
	mstruct->map = tab;
	return (mstruct);
}
