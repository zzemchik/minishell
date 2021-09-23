#include "minishell.h"

void	parse_env_vars(char **envp)
{
	char	*key;
	char	*value;
	int		i;
	int		j;

	i = -1;
	while (envp[++i])
	{
		j = 0;
		while (envp[i][j] != '=')
			j++;
		key = ft_strndup(envp[i], j);
		value = ft_strdup(envp[i] + j + 1);
		add_var(key, value, &g_vars_list, 1);
	}
	value = get_value("SHLVL", g_vars_list);
	if (value)
	{
		i = ft_atoi(value);
		add_var(ft_strdup("SHLVL"), ft_itoa(i + 1), &g_vars_list, 1);
	}
}

char	*key_value_to_char(char *key, char *value)
{
	char	*temp;
	char	*result;

	temp = ft_strjoin(key, "=");
	result = ft_strjoin(temp, value);
	free_if_exist(temp);
	return (result);
}

void	vars_to_array_norm(t_env_var *temp, char **result, int *i, char *name)
{
	if (temp->value)
	{
		if (!ft_strcmp(temp->key, "_"))
			result[*i] = key_value_to_char(temp->key, temp->value);
		else
			result[*i] = key_value_to_char(temp->key, name);
	}
	else
		(*i)--;
}

char	**vars_to_array(char *name)
{
	t_env_var	*temp;
	int			size;
	char		**result;
	int			i;

	temp = g_vars_list;
	size = 0;
	while (temp)
	{
		if (temp->value)
			size++;
		temp = temp->next;
	}
	if (!(result = malloc(sizeof(char*) * (size + 1))))
		exita(0);
	result[size] = 0;
	i = -1;
	temp = g_vars_list;
	while (++i < size)
	{
		vars_to_array_norm(temp, result, &i, name);
		temp = temp->next;
	}
	return (result);
}

void	add_reminder(char *temp, int i, char **result)
{
	int		j;
	char	*t;
	char	*tmp;

	if (temp[i] != 0)
	{
		t = *result;
		if (!ft_strchr(temp, '$'))
			*result = ft_strjoin(*result, temp + i);
		else
		{
			j = i;
			while (temp[j] != '$')
				j++;
			tmp = ft_strndup(temp + i, j - i);
			*result = ft_strjoin(*result, tmp);
			free_if_exist(tmp);
		}
		free_if_exist(t);
	}
}
