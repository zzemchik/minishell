/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_equally.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmass <rmass@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/20 00:00:01 by rmass             #+#    #+#             */
/*   Updated: 2021/04/03 22:37:15 by rmass            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	apply_equally(t_list **list)
{
	t_list	*temp;
	char	*key;
	char	*value;
	int		i;

	temp = *list;
	while (temp && !ft_strcmp(temp->data, "|") && !ft_strcmp(temp->data, ";"))
	{
		i = 0;
		while ((temp->data)[i] != '=')
			i++;
		key = ft_strndup((*list)->data, i);
		value = ft_strdup((*list)->data + i + 1);
		add_var(key, value, &g_temp_vars_list, 1);
		temp = temp->next;
		if ((*list)->next && !ft_strcmp((*list)->next->data, ";"))
			free_one_list(list);
	}
	return (1);
}
