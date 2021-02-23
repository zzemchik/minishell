/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_equally.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnancee <rnancee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/20 00:00:01 by rmass             #+#    #+#             */
/*   Updated: 2021/02/23 18:29:37 by rnancee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	apply_equally(t_list **list)
{
	t_list	*temp;
	char	*key;
	char	*value;
	int		i;

	if (!ft_strchr((*list)->data, '=') || \
	((*list)->next && ((*list)->next->data)[0] == 0))
		return (0);
	if ((*list)->next && !(ft_strcmp((*list)->next->data, "|") || \
	ft_strcmp((*list)->next->data, ";")))
	{
		free_one_list(list);
		return (0);
	}
	i = 0;
	while ((*list)->data[i] != '=')
		i++;
	key = ft_strndup((*list)->data, i);
	value = ft_strdup((*list)->data + i + 1);
	add_var(key, value, &g_temp_vars_list);
	return (1);
}
