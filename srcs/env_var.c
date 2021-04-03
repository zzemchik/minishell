/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_var.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmass <rmass@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/15 18:47:02 by rmass             #+#    #+#             */
/*   Updated: 2021/04/03 22:36:40 by rmass            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char		*get_value(char *key, t_env_var *vars)
{
	t_env_var	*temp;

	if (ft_strcmp(key, "?"))
		return (ft_itoa(g_ret_value));
	temp = vars;
	while (temp)
	{
		if (ft_strcmp(temp->key, key))
			return (temp->value);
		temp = temp->next;
	}
	return (0);
}

static void	push_front(char *key, char *value, t_env_var **list)
{
	t_env_var	*new;

	if (!(new = malloc(sizeof(t_env_var))))
		exita(0);
	new->key = key;
	new->value = value;
	new->next = 0;
	if (*list == 0)
		*list = new;
	else if (new)
	{
		new->next = *list;
		*list = new;
	}
}

void		add_var(char *key, char *value, t_env_var **list, int flag)
{
	t_env_var	*temp;

	if (!get_value(key, g_temp_vars_list) && \
	!get_value(key, g_vars_list) && !key_exist(key))
		push_front(key, value, list);
	else
	{
		temp = g_vars_list;
		while (temp || (flag && g_temp_vars_list))
		{
			if (flag && !temp && (flag = 0) == 0)
				temp = g_temp_vars_list;
			if (ft_strcmp(temp->key, key))
			{
				free_if_exist(temp->value);
				temp->value = 0;
				temp->value = value;
				free_if_exist(key);
				return ;
			}
			temp = temp->next;
		}
		free_if_exist(key);
	}
}

void		display_all_vars(void)
{
	t_env_var	*temp;

	temp = g_vars_list;
	while (temp)
	{
		if (temp->value)
		{
			ft_putstr(temp->key);
			ft_putstr("=");
			ft_putstr(temp->value);
			ft_putstr("\n");
		}
		temp = temp->next;
	}
}

int			check_last_dollar(char *temp, char **result)
{
	char	*t;

	if (temp[1] == 0 || (ft_strchr("\"\'", temp[1]) && temp[2] == 0))
	{
		t = *result;
		*result = ft_strjoin(*result, temp);
		free_if_exist(t);
		return (1);
	}
	return (0);
}
