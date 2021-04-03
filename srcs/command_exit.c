/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnancee <rnancee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/12 02:42:03 by rmass             #+#    #+#             */
/*   Updated: 2021/04/01 21:02:59 by rnancee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	numeric_error(t_list **list)
{
	ft_putstr("exit\nminishell: exit: ");
	ft_putstr((*list)->data);
	ft_putstr(": numeric argument required\n");
	free_full_list(list);
	exita(255);
}

void	command_exit(t_list **list)
{
	int		i;

	free_one_list(list);
	if (!(*list))
		exita(0);
	i = -1;
	if ((((*list)->data)[0] == '-' && ft_strlen((*list)->data) > 20) \
	|| (((*list)->data)[0] != '-' && ft_strlen((*list)->data) > 19))
		numeric_error(list);
	while (((*list)->data)[++i])
		if (!is_num(((*list)->data)[i]) && \
		!(i == 0 && (((*list)->data)[i] == '-' || ((*list)->data)[i] == '+')))
			numeric_error(list);
	if ((*list)->next)
	{
		ft_putstr("exit\nminishell: exit: ");
		ft_putstr((*list)->data);
		ft_putstr(": too many arguments\n");
		g_ret_value = 1;
		skip(list);
		return ;
	}
	i = ft_atoi((*list)->data);
	free_full_list(list);
	exita((char)i);
}
