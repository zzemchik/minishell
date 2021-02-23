/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   all_zero_free.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnancee <rnancee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/16 13:59:56 by rnancee           #+#    #+#             */
/*   Updated: 2021/02/23 20:48:42 by rnancee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	all_zero(char **argc)
{
	g_flag_write = 1;
	g_ret_value = 0;
	g_temp_vars_list = 0;
	g_current_folder = *argc;
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
