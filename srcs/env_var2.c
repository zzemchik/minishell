/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_var2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmass <rmass@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/20 16:49:53 by rmass             #+#    #+#             */
/*   Updated: 2021/02/21 22:24:09 by rmass            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
	if (flag)
	{
		*result = ft_strjoin(*result, "$");
		free_if_exist(t);
		t = *result;
		*result = ft_strjoin(*result, key);
	}
	else if (get_value(key, g_vars_list))
		*result = ft_strjoin(*result, get_value(key, g_vars_list));
	else
		*result = ft_strjoin(*result, get_value(key, g_temp_vars_list));
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
		while (is_alpha(temp[i]) || (i > 0 && is_num(temp[i])))
			i++;
		key = ft_strndup(temp, i);
		t = *result;
		rep_vars_norm(result, key, flag, t);
		flag = is_in_single_quotes(temp);
		if (!ft_strchr(temp, '$') && temp[i] != 0)
		{
			t = *result;
			*result = ft_strjoin(*result, ft_strdup(temp + i));
			free_if_exist(t);
		}
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
		*result = ft_strdup(list->data);
	rep_vars(list->data, result);
}

void		replace_vars(t_list *list)
{
	char	*temp;
	char	*result;

	while (list)
	{
		result = 0;
		temp = list->data;
		replace(list, &result);
		list->data = result;
		free_if_exist(temp);
		list = list->next;
	}
}
