#include "minishell.h"

int	apply_equally(t_list **list)
{
	t_list	*temp;
	char	*key;
	char	*value;
	int		i;

	temp = *list;
	while (temp && !ft_strcmp(temp->data, "|") && !ft_strcmp(temp->data, ";"))
	{
		i = 0;
		while ((temp->data)[i] != '=')
			i++;
		key = ft_strndup((*list)->data, i);
		value = ft_strdup((*list)->data + i + 1);
		add_var(key, value, &g_temp_vars_list, 1);
		temp = temp->next;
		if ((*list)->next && !ft_strcmp((*list)->next->data, ";"))
			free_one_list(list);
	}
	return (1);
}
