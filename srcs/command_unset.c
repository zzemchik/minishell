/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_unset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnancee <rnancee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/20 17:11:18 by rmass             #+#    #+#             */
/*   Updated: 2021/02/23 18:57:05 by rnancee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void		unset(t_list **list)
{
	t_list	*temp;

	temp = *list;
	while (temp->next && !ft_strcmp(temp->next->data, "|") && \
	!ft_strcmp(temp->next->data, ";"))
	{
		if (ft_strlen(temp->next->data) > 0 && is_alpha((temp->next->data)[0]))
		{
			if (get_value(temp->next->data, g_temp_vars_list))
				remove_value(&g_temp_vars_list, temp->next->data);
			if (get_value(temp->next->data, g_vars_list))
				remove_value(&g_vars_list, temp->next->data);
		}
		temp = temp->next;
	}
	skip(list);
	save_env_vars();
}
