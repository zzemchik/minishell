/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   equally.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmass <rmass@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/04 17:24:56 by rmass             #+#    #+#             */
/*   Updated: 2021/03/20 20:23:01 by rmass            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	del_if_eq(t_list **list, t_list *el)
{
	t_list	*temp;

	if (*list == el)
		*list = (*list)->next;
	else
	{
		temp = *list;
		while (temp->next)
		{
			if (temp->next == el)
			{
				temp->next = temp->next->next;
				break ;
			}
			temp = temp->next;
		}
	}
	free_if_exist(el->data);
	free(el);
}

int			correct_equal(char *str)
{
	int		eq_start;
	int		i;

	eq_start = 0;
	i = -1;
	if (!ft_strchr(str, '='))
		return (0);
	while (str[eq_start] != '=')
		eq_start++;
	if (!is_alpha(str[0]) && str[0] != '_' && str[0] != '?')
		return (0);
	while (++i < eq_start)
		if (!is_alpha(str[i]) && str[i] != '_' && !is_num(str[i]))
			return (0);
	return (1);
}

void		add_el(t_list_list **list, t_list *el)
{
	t_list_list	*temp;

	temp = malloc(sizeof(t_list_list));
	temp->data = el;
	temp->next = 0;
	if (*list)
		temp->next = *list;
	*list = temp;
}

void		find_equally_norm(t_list *start, int flag, t_list_list **del_list)
{
	t_list	*temp;

	temp = start;
	while (temp && !ft_strcmp(temp->data, ";") && !flag)
	{
		if (ft_strcmp(temp->data, "|") || !correct_equal(temp->data))
			flag = 1;
		temp = temp->next;
	}
	if (flag)
	{
		temp = start;
		while (temp && !ft_strcmp(temp->data, ";"))
		{
			if (correct_equal(temp->data))
				add_el(del_list, temp);
			else
			{
				while (temp->next && !ft_strcmp(temp->next->data, "|") \
				&& !ft_strcmp(temp->next->data, ";"))
					temp = temp->next;
			}
			temp = temp->next;
		}
	}
}

void		find_equally(t_list **list)
{
	t_list_list	*del_list_temp;
	t_list_list	*del_list;
	t_list		*start;

	del_list = 0;
	start = *list;
	while (start)
	{
		find_equally_norm(start, 0, &del_list);
		while (start && !ft_strcmp(start->data, ";"))
			start = start->next;
		if (start && ft_strcmp(start->data, ";"))
			start = start->next;
	}
	while (del_list)
	{
		del_list_temp = del_list;
		del_if_eq(list, del_list->data);
		del_list = del_list->next;
		free(del_list_temp);
	}
}
