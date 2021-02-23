/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnancee <rnancee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/17 17:08:38 by rnancee           #+#    #+#             */
/*   Updated: 2021/02/23 20:48:42 by rnancee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	command_echo(t_list **list)
{
	int		flag_n;

	flag_n = 0;
	free_one_list(list);
	if ((*list) && ft_strcmp((*list)->data, "-n") == 1 && (flag_n = 1))
		free_one_list(list);
	while (*list)
	{
		if (ft_strcmp((*list)->data, "|") || ft_strcmp((*list)->data, ";"))
			break ;
		ft_putstr((*list)->data);
		ft_putstr(" ");
		free_one_list(list);
	}
	ft_putstr("\b");
	if (flag_n == 0)
		ft_putstr("\n");
	else
		ft_putstr("%\n");
}
