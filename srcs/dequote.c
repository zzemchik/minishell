/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dequote.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnancee <rnancee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/20 14:36:05 by rmass             #+#    #+#             */
/*   Updated: 2021/04/01 18:38:21 by rnancee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	change_list_data(char *result, char **data)
{
	char	*temp;

	temp = ft_strdup(result);
	free_if_exist(result);
	free_if_exist(*data);
	*data = temp;
}

static int	check_quote(char temp, char *in_quote, char *type)
{
	if (*in_quote)
	{
		if (temp != *type)
			return (1);
		else
			*in_quote = 0;
	}
	else
	{
		*in_quote = 1;
		*type = temp;
	}
	return (0);
}

int			set_vars(int *i, int *j, char **result, t_list *list)
{
	*result = malloc(ft_strlen(list->data) + 1);
	*i = -1;
	*j = -1;
	return (0);
}

void		dequote(t_list *list)
{
	char	*result;
	char	in_quote;
	char	type;
	int		i;
	int		j;

	while (list && !ft_strcmp(list->data, ";"))
	{
		in_quote = set_vars(&i, &j, &result, list);
		while (list->data && (list->data)[++i])
		{
			if ((list->data)[i] == '\\' && (list->data)[i + 1] != '\'')
			{
				result[++j] = (list->data)[i++];
				result[++j] = (list->data)[i];
			}
			else if ((list->data)[i] != '\'' && (list->data)[i] != '\"')
				result[++j] = (list->data)[i];
			else if (check_quote((list->data)[i], &in_quote, &type))
				result[++j] = (list->data)[i];
		}
		result[++j] = 0;
		change_list_data(result, &(list->data));
		list = list->next;
	}
}
