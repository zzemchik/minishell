/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnancee <rnancee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/21 20:22:11 by rmass             #+#    #+#             */
/*   Updated: 2021/02/23 18:58:10 by rnancee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	find_and_remove(char *key, char **value)
{
	if (*value)
		return ;
	if (get_value(key, g_temp_vars_list))
		*value = ft_strdup(get_value(key, g_temp_vars_list));
	remove_value(&g_temp_vars_list, key);
}

static void	export_norm(char **key, char **value, t_list *temp, int i)
{
	*key = ft_strndup(temp->next->data, i);
	*value = 0;
	if ((temp->next->data)[i])
		*value = ft_strdup(temp->next->data + i + 1);
	find_and_remove(*key, value);
	if (*value)
		add_var(*key, *value, &g_vars_list);
}

void		export(t_list **list)
{
	int		i;
	char	*key;
	char	*value;
	t_list	*temp;

	temp = *list;
	while (temp->next && !ft_strcmp(temp->next->data, "|") && \
	!ft_strcmp(temp->next->data, ";"))
	{
		if (ft_strlen(temp->next->data) > 0 && is_alpha((temp->next->data)[0]))
		{
			i = 0;
			while ((temp->next->data)[i] && (temp->next->data)[i] != '=')
			{
				if (is_alpha((temp->next->data)[i]) || \
				is_num((temp->next->data)[i]))
					i++;
				else
					return ;
			}
			export_norm(&key, &value, temp, i);
		}
		temp = temp->next;
	}
	skip(list);
	save_env_vars();
}
