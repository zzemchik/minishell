/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   equally.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmass <rmass@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/19 22:29:59 by rmass             #+#    #+#             */
/*   Updated: 2021/02/21 18:40:14 by rmass            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	add_space(t_list *list)
{
	t_list	*temp;

	if (!(temp = malloc(sizeof(t_list))))
		exita();
	temp->data = ft_strdup("");
	temp->next = list->next;
	list->next = temp;
}

static void	find_equally_norm(int eq_start, int qu_start, t_list *list)
{
	int	i;

	if (qu_start < eq_start)
		add_space(list);
	else
	{
		i = -1;
		while (++i < eq_start)
		{
			if (!is_alpha(list->data[i]) && !(i > 0 && is_num(list->data[i])))
			{
				add_space(list);
				break ;
			}
		}
	}
}

void		find_equally(t_list *list)
{
	int		eq_start;
	int		qu_start;

	while (list)
	{
		if (ft_strchr(list->data, '='))
		{
			eq_start = 0;
			while (list->data[eq_start] != '=')
				eq_start++;
			qu_start = 0;
			while (list->data[qu_start] != '\'' && \
			list->data[qu_start] != '\"' && list->data[qu_start] != 0)
				qu_start++;
			find_equally_norm(eq_start, qu_start, list);
		}
		while (list && list->next && !ft_strcmp(list->next->data, "|") \
		&& !ft_strcmp(list->next->data, ";"))
			list = list->next;
		if (list)
			list = list->next;
	}
}
