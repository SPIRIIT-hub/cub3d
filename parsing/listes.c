#include "../headers/cub3d.h"
#include "../headers/get_next_line.h"

t_list	*ft_lstnew(void *content)
{
	t_list	*liste;

	liste = wrmalloc(sizeof(t_list));
	if (!(liste))
		return (NULL);
	liste->content = content;
	liste->next = NULL;
	return (liste);
}

void	ft_lstadd_back(t_list **alst, t_list *new)
{
	t_list	*ok;

	if (*alst == NULL)
	{
		*alst = new;
		return ;
	}
	ok = *alst;
	while (ok->next != NULL)
		ok = ok->next;
	ok->next = new;
}

void	ft_lstclear(t_list **lst, void (*del)(void*))
{
	t_list	*ok;

	ok = (*lst);
	while (ok != NULL)
	{
		ok = (*lst)->next;
		del((*lst)->content);
		wrfree((*lst));
		(*lst) = ok;
	}
	(*lst) = NULL;
}

int	ft_lstsize(t_list *lst)
{
	int	i;

	i = 0;
	while (lst != NULL)
	{
		lst = lst->next;
		i++;
	}
	return (i);
}

t_list	*makelst(int fd, t_struct *mstruct)
{
	t_list	*thelist;
	char	*line;
	int		result;
	t_list	*new;

	result = 1;
	line = NULL;
	thelist = NULL;
	while (result == 1)
	{
		result = get_next_line(fd, &line);
		mstruct->i = shouldiskip(line, mstruct);
		if (mstruct->i == 0)
		{
			new = ft_lstnew(line);
			ft_lstadd_back(&thelist, new);
		}
		if (mstruct->i == -1)
			return (error_makelst(&line, thelist));
		if (mstruct->i != 0)
			free(line);
	}
	return (thelist);
}
