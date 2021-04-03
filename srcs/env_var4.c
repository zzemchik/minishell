/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_var4.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmass <rmass@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/03 21:55:11 by rmass             #+#    #+#             */
/*   Updated: 2021/04/03 21:56:27 by rmass            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int			key_exist(char *key)
{
	t_env_var	*temp;

	temp = g_vars_list;
	while (temp)
	{
		if (ft_strcmp(temp->key, key))
			return (1);
		temp = temp->next;
	}
	temp = g_temp_vars_list;
	while (temp)
	{
		if (ft_strcmp(temp->key, key))
			return (2);
		temp = temp->next;
	}
	return (0);
}
