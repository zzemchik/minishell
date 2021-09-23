#include "minishell.h"

void		remove_first_value(t_env_var **list)
{
	t_env_var	*t;

	t = (*list);
	*list = (*list)->next;
	free_if_exist(t->key);
	free_if_exist(t->value);
	free(t);
}

void		remove_value(t_env_var **list, char *key)
{
	t_env_var	*temp;
	t_env_var	*t;

	if (!(*list))
		return ;
	if (ft_strcmp((*list)->key, key))
	{
		remove_first_value(list);
		return ;
	}
	temp = *list;
	while (temp->next)
	{
		if (ft_strcmp(temp->next->key, key))
		{
			t = temp->next;
			free_if_exist(temp->next->key);
			free_if_exist(temp->next->value);
			temp->next = temp->next->next;
			free(t);
			return ;
		}
		temp = temp->next;
	}
}

void		unset(t_list **list)
{
	t_list	*temp;

	temp = *list;
	g_ret_value = 0;
	while (temp->next && !ft_strcmp(temp->next->data, "|") && \
	!ft_strcmp(temp->next->data, ";"))
	{
		if (ft_strlen(temp->next->data) > 0 && is_alpha((temp->next->data)[0]))
		{
			if (get_value(temp->next->data, g_temp_vars_list) \
			|| key_exist(temp->next->data) == 2)
				remove_value(&g_temp_vars_list, temp->next->data);
			if (get_value(temp->next->data, g_vars_list) \
			|| key_exist(temp->next->data) == 1)
				remove_value(&g_vars_list, temp->next->data);
		}
		temp = temp->next;
	}
	skip(list);
}
