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
