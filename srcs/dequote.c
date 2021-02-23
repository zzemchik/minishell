/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dequote.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmass <rmass@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/20 14:36:05 by rmass             #+#    #+#             */
/*   Updated: 2021/02/21 18:44:07 by rmass            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	add_one(char **str, char c)
{
	int		i;
	int		len;
	char	*result;

	len = ft_strlen(*str);
	result = malloc(len + 2);
	i = 0;
	while ((*str) && (*str)[i])
	{
		result[i] = (*str)[i];
		i++;
	}
	result[i] = c;
	result[i + 1] = 0;
	free_if_exist(*str);
	*str = result;
}

static void	check_quote(char **result, char temp, char *in_quote, char *type)
{
	if (*in_quote)
	{
		if (temp != *type)
			add_one(result, temp);
		else
			*in_quote = 0;
	}
	else
	{
		*in_quote = 1;
		*type = temp;
	}
}

void		dequote(t_list *list)
{
	char	*result;
	char	in_quote;
	char	type;
	int		i;

	while (list)
	{
		in_quote = 0;
		result = 0;
		i = -1;
		while (list->data && (list->data)[++i])
		{
			if ((list->data)[i] != '\'' && (list->data)[i] != '\"')
				add_one(&result, (list->data)[i]);
			else
				check_quote(&result, (list->data)[i], &in_quote, &type);
		}
		if ((list->data)[0] != 0)
		{
			free_if_exist(list->data);
			list->data = result;
		}
		list = list->next;
	}
}
