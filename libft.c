/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmoulin <bmoulin@42lyon.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/24 09:20:56 by bmoulin           #+#    #+#             */
/*   Updated: 2021/02/24 09:21:19 by bmoulin          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_list		*ft_lstlast(t_list *lst)
{
	if (!lst)
		return (lst);
	while (lst->next)
		lst = lst->next;
	return (lst);
}

void	ft_lstadd_back(t_list **alst, t_list *new)
{
	t_list		*tmp;

	if (*alst == NULL)
		*alst = new;
	else
	{
		tmp = ft_lstlast(*alst);
		tmp->next = new;
		tmp->next->next = NULL;
	}
}
