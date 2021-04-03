/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_export2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmass <rmass@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/24 20:07:03 by rmass             #+#    #+#             */
/*   Updated: 2021/03/24 20:25:52 by rmass            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	parse_array(char ***arr)
{
	int			size;
	t_env_var	*temp;
	int			ret;

	size = 0;
	temp = g_vars_list;
	while (temp)
	{
		if (!ft_strcmp(temp->key, "_"))
			size++;
		temp = temp->next;
	}
	ret = size;
	*arr = malloc(sizeof(char *) * (size + 1));
	(*arr)[size] = 0;
	temp = g_vars_list;
	while (--size >= 0)
	{
		if (!ft_strcmp(temp->key, "_"))
			(*arr)[size] = temp->key;
		else
			size++;
		temp = temp->next;
	}
	return (ret);
}

void		print_export(void)
{
	char		**arr;
	char		*value;
	int			size;
	int			i;

	arr = 0;
	size = parse_array(&arr);
	sort_array(arr, size);
	i = -1;
	while (arr[++i])
	{
		ft_putstr("declare -x ");
		ft_putstr(arr[i]);
		value = get_value(arr[i], g_vars_list);
		if (value)
		{
			write(1, "=", 1);
			ft_putstr(value);
		}
		write(1, "\n", 1);
	}
	i = -1;
	free(arr);
}
