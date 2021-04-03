/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   all_zero_free.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmass <rmass@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/16 13:59:56 by rnancee           #+#    #+#             */
/*   Updated: 2021/03/25 04:43:27 by rmass            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	all_zero(void)
{
	g_ret_value = 0;
	g_temp_vars_list = 0;
	g_flag = 0;
	g_ctrl_c = 0;
	g_ctrl_s = 0;
}

void	free_one_list(t_list **list)
{
	t_list *tmp;

	tmp = *list;
	if (tmp && tmp->data)
		free(tmp->data);
	if (*list)
		(*list) = (*list)->next;
	if (tmp)
		free(tmp);
}
