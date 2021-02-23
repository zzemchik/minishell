/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnancee <rnancee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/17 16:32:38 by rnancee           #+#    #+#             */
/*   Updated: 2021/02/22 17:23:40 by rnancee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	command_cd(t_list **list)
{
	t_list *tmp;

	tmp = *list;
	if ((*list)->next)
	{
		*list = (*list)->next;
		if (tmp)
			free(tmp);
		if (chdir((*list)->data) == -1)
		{
			ft_putstr("cd: no such file or directory: ");
			ft_putstr((*list)->data);
			ft_putstr("\n");
		}
	}
	else
		chdir("/Users");
	skip(list);
}
