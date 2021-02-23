/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lists_int.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnancee <rnancee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/14 18:25:57 by rnancee           #+#    #+#             */
/*   Updated: 2021/02/22 19:07:16 by rnancee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_lstadd_back_int(t_list_int **lst, t_list_int *lst_new)
{
	t_list_int *a;

	if (*lst == NULL)
		*lst = lst_new;
	else
	{
		a = ft_lstlast(*lst);
		(a)->next = lst_new;
		a->next->next = 0;
	}
}

t_list_int	*ft_lstlast_int(t_list_int *lst)
{
	t_list_int	*lst_cpy;

	if (lst == 0)
		return (0);
	lst_cpy = lst;
	while (lst_cpy->next)
		lst_cpy = lst_cpy->next;
	return (lst_cpy);
}

t_list_int	*ft_lstnew_int(int content)
{
	t_list_int	*n_elem;

	if (!(n_elem = malloc(sizeof(t_list_int))))
		return (NULL);
	n_elem->data = content;
	n_elem->next = NULL;
	return (n_elem);
}

int		ft_lstsize_int(t_list_int *lst)
{
	int			i;
	t_list_int	*lst_copy;

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

t_list_int	*lst_int_push_front(t_list_int **lst, int data)
{
	t_list_int	*new;

	if (!(new = malloc(sizeof(t_list_int))))
		return (0);
	new->data = data;
	new->next = 0;
	if (*lst)
		new->next = *lst;
	*lst = new;
}
