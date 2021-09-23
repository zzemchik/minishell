#include "minishell.h"

void	ft_lstadd_back(t_list **lst, t_list *lst_new)
{
	t_list *a;

	if (*lst == NULL)
		*lst = lst_new;
	else
	{
		a = ft_lstlast(*lst);
		(a)->next = lst_new;
	}
}

t_list	*ft_lstlast(t_list *lst)
{
	t_list	*lst_cpy;

	if (lst == 0)
		return (0);
	lst_cpy = lst;
	while (lst_cpy->next)
		lst_cpy = lst_cpy->next;
	return (lst_cpy);
}

t_list	*ft_lstnew(char *content)
{
	t_list	*n_elem;

	if (!(n_elem = malloc(sizeof(t_list))))
		return (NULL);
	n_elem->data = content;
	n_elem->next = NULL;
	return (n_elem);
}

int		ft_lstsize(t_list *lst)
{
	int		i;
	t_list	*lst_copy;

	if (lst == 0)
		return (0);
	lst_copy = lst;
	if (!lst)
		return (0);
	i = 0;
	while (lst_copy->next != 0)
	{
		lst_copy = lst_copy->next;
		i++;
	}
	return (++i);
}
