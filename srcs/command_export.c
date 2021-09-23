#include "minishell.h"

void	find_and_remove(char *key, char **value)
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
	add_var(*key, *value, &g_vars_list, 1);
}

static void	export_loop(t_list **temp, int i)
{
	char	*key;
	char	*value;
	int		flag;

	flag = 0;
	if (ft_strlen((*temp)->next->data) > 0 \
	&& is_alpha(((*temp)->next->data)[0]))
	{
		i = 0;
		while (((*temp)->next->data)[i] && ((*temp)->next->data)[i] != '=')
		{
			if (is_alpha(((*temp)->next->data)[i]) || \
			is_num(((*temp)->next->data)[i]) || ((*temp)->next->data)[i] == '_')
				i++;
			else
			{
				flag = 1;
				break ;
			}
		}
		if (flag == 0)
			export_norm(&key, &value, (*temp), i);
	}
	if (is_num((*temp)->next->data[0]) || flag)
	{
		ft_putstr("minishell: export: \'");
		ft_putstr((*temp)->next->data);
		ft_putstr("\': not a valid identifier\n");
		g_ret_value = 1;
	}
	(*temp) = (*temp)->next;
}

void		export(t_list **list)
{
	t_list	*temp;

	temp = *list;
	g_ret_value = 0;
	if (!(temp->next) || ft_strcmp(temp->next->data, "|") || \
	ft_strcmp(temp->next->data, ";") || ft_strcmp(temp->next->data, ">") || \
	ft_strcmp(temp->next->data, ">>") || ft_strcmp(temp->next->data, "<"))
		print_export();
	while (temp->next && !ft_strcmp(temp->next->data, "|") && \
	!ft_strcmp(temp->next->data, ";"))
		export_loop(&temp, 0);
	skip(list);
}
