#include "minishell.h"

static int	is_in_single_quotes(char *temp)
{
	char	type;
	int		dollar_pos;
	int		qstrt;
	int		qend;

	if (!ft_strchr(temp, '\'') || !ft_strchr(temp, '$'))
		return (0);
	dollar_pos = 0;
	while (temp[dollar_pos] != '$')
		dollar_pos++;
	qend = -1;
	while ((qstrt = qend + 1) == qend + 1)
	{
		while (temp[qstrt] != '\'' && temp[qstrt] != '\"' && temp[qstrt] != 0)
			qstrt++;
		if (dollar_pos < qstrt || temp[qstrt] == 0)
			return (0);
		type = temp[qstrt];
		qend = qstrt + 1;
		while (temp[qend] != type)
			qend++;
		if (dollar_pos < qend)
			return (type == '\'');
	}
	return (0);
}

static void	rep_vars_norm(char **result, char *key, int flag, char *t)
{
	char	*value;

	value = get_value(key, g_vars_list);
	if (flag)
	{
		*result = ft_strjoin(*result, "$");
		free_if_exist(t);
		t = *result;
		*result = ft_strjoin(*result, key);
	}
	else if (value)
		*result = ft_strjoin(*result, value);
	else
		*result = ft_strjoin(*result, get_value(key, g_temp_vars_list));
	if (ft_strcmp(key, "?"))
		free_if_exist(value);
	free_if_exist(t);
	free_if_exist(key);
}

static void	rep_vars(char *temp, char **result)
{
	char	*key;
	char	*t;
	int		i;
	int		flag;

	flag = is_in_single_quotes(temp);
	while ((temp = ft_strchr(temp, '$')))
	{
		if (check_last_dollar(temp, result))
			return ;
		temp++;
		i = 0;
		while (temp[i] && temp[i] != ' ' && temp[i] != '\"' \
		&& temp[i] != '\'' && temp[i] != '$')
			i++;
		key = ft_strndup(temp, i);
		t = *result;
		rep_vars_norm(result, key, flag, t);
		add_reminder(temp, i, result);
	}
}

static void	replace(t_list *list, char **result)
{
	int		i;

	if (ft_strchr(list->data, '$'))
	{
		i = 0;
		while (list->data[i] != '$')
			i++;
		*result = ft_strndup(list->data, i);
	}
	else
		return ;
	rep_vars(list->data, result);
}

void		replace_vars(t_list *list)
{
	char	*temp;
	char	*result;

	while (list && !ft_strcmp(list->data, ";"))
	{
		result = 0;
		temp = list->data;
		replace(list, &result);
		if (result)
		{
			list->data = result;
			free_if_exist(temp);
		}
		list = list->next;
	}
}
