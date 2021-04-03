/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmass <rmass@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/17 17:08:38 by rnancee           #+#    #+#             */
/*   Updated: 2021/03/23 21:11:38 by rmass            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	command_echo(t_list **list)
{
	int		flag_n;

	flag_n = 0;
	free_one_list(list);
	while ((*list) && ft_strcmp((*list)->data, "-n") == 1 && (flag_n = 1))
		free_one_list(list);
	while (*list)
	{
		if (ft_strcmp((*list)->data, "|") || ft_strcmp((*list)->data, ";") || \
		ft_strcmp((*list)->data, ">") || ft_strcmp((*list)->data, ">>") || \
		ft_strcmp((*list)->data, "<"))
			break ;
		ft_putstr((*list)->data);
		if ((*list)->next && !(ft_strcmp((*list)->next->data, "|") \
		|| ft_strcmp((*list)->next->data, ";")))
			ft_putstr(" ");
		free_one_list(list);
	}
	if (flag_n == 0)
		ft_putstr("\n");
	g_ret_value = 0;
}
